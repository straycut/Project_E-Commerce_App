// courierForm.cpp - Implementation of courierForm event handlers
#include "courierForm.h"

namespace ECommerce {

System::Void courierForm::courierForm_Load(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  // Apply DGV theming
  array<DataGridView ^> ^ grids = {dgvPending, dgvActive, dgvHistory};
  for each (DataGridView ^ dgv in grids) {
    dgv->BackgroundColor = System::Drawing::Color::White;
    dgv->BorderStyle = System::Windows::Forms::BorderStyle::None;
    dgv->EnableHeadersVisualStyles = false;
    dgv->ColumnHeadersDefaultCellStyle->BackColor =
        System::Drawing::Color::FromArgb(46, 125, 50);
    dgv->ColumnHeadersDefaultCellStyle->ForeColor =
        System::Drawing::Color::White;
    dgv->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
    dgv->DefaultCellStyle->SelectionBackColor =
        System::Drawing::Color::FromArgb(200, 230, 201);
    dgv->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
    dgv->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
    dgv->GridColor = System::Drawing::Color::FromArgb(224, 224, 224);
    dgv->RowTemplate->Height = 32;
    dgv->AlternatingRowsDefaultCellStyle->BackColor =
        System::Drawing::Color::FromArgb(245, 247, 250);
    dgv->ColumnHeadersHeight = 36;
  }

  LoadDashboard();
  LoadPending();
  LoadActive();
  LoadHistory();
}

void courierForm::LoadDashboard() {
  array<int> ^ stats = DatabaseManager::GetCourierStats(currentUserID);
  lblTodayDeliveries->Text = L"Pengiriman Hari Ini: " + stats[0];
  lblTotalDeliveries->Text = L"Total Pengiriman: " + stats[1];
  lblTotalIncome->Text =
      L"Pendapatan: Rp " + String::Format("{0:N0}", stats[2]);

  // Display current balance
  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblCurrentBalance->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

void courierForm::LoadPending() {
  dgvPending->DataSource = DatabaseManager::GetPendingDeliveries();
}

void courierForm::LoadActive() {
  dgvActive->DataSource = DatabaseManager::GetActiveDeliveries(currentUserID);
}

void courierForm::LoadHistory() {
  dgvHistory->DataSource = DatabaseManager::GetDeliveryHistory(currentUserID);
}

System::Void courierForm::btnRefreshDashboard_Click(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  LoadDashboard();
  MessageBox::Show("Dashboard diperbarui!", "Info", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
}

System::Void courierForm::btnRefreshPending_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  LoadPending();
}

System::Void courierForm::btnClaim_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
  if (dgvPending->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan yang akan diambil!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int count = dgvPending->SelectedRows->Count;
  if (MessageBox::Show("Ambil " + count + " pesanan yang dipilih?",
                       "Konfirmasi", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    int success = 0;
    int fail = 0;
    for (int i = 0; i < dgvPending->SelectedRows->Count; i++) {
      int transID =
          Convert::ToInt32(dgvPending->SelectedRows[i]->Cells["ID"]->Value);
      if (DatabaseManager::ClaimDelivery(transID, currentUserID)) {
        success++;
      } else {
        fail++;
      }
    }

    String ^ msg = "Berhasil mengambil " + success + " pesanan.";
    if (fail > 0)
      msg += "\n" + fail + " pesanan gagal (mungkin sudah diambil kurir lain).";

    MessageBox::Show(msg, "Hasil", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    LoadPending();
    LoadActive();
    LoadDashboard();
  }
}

System::Void courierForm::btnRefreshActive_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  LoadActive();
}

System::Void courierForm::btnComplete_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  if (dgvActive->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pengiriman yang sudah selesai!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int count = dgvActive->SelectedRows->Count;
  if (MessageBox::Show("Selesaikan " + count +
                           " pengiriman?\nAnda akan menerima ongkos kirim.",
                       "Konfirmasi", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    int success = 0;
    int fail = 0;
    for (int i = 0; i < dgvActive->SelectedRows->Count; i++) {
      int transID =
          Convert::ToInt32(dgvActive->SelectedRows[i]->Cells["ID"]->Value);
      if (DatabaseManager::CompleteDelivery(transID, currentUserID)) {
        success++;
      } else {
        fail++;
      }
    }

    String ^ msg = "Berhasil: " + success + " pengiriman selesai.";
    if (fail > 0)
      msg += "\n" + fail + " pengiriman gagal.";
    msg += "\n\nOngkos kirim telah ditambahkan ke saldo Anda.";

    MessageBox::Show(msg, "Hasil", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    LoadActive();
    LoadHistory();
    LoadDashboard();
  }
}

System::Void courierForm::btnRefreshHistory_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  LoadHistory();
}

System::Void courierForm::btnWithdraw_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  int amount = 0;
  if (!Int32::TryParse(txtWithdrawAmount->Text, amount) || amount <= 0) {
    MessageBox::Show("Masukkan jumlah penarikan yang valid (angka positif)!",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  // Check current balance
  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  if (amount > currentSaldo) {
    MessageBox::Show(
        "Saldo tidak cukup!\\n\\nJumlah penarikan: Rp " +
            String::Format("{0:N0}", amount) + "\\nSaldo Anda: Rp " +
            String::Format("{0:N0}", currentSaldo),
        "Saldo Tidak Cukup", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Tarik saldo sebesar Rp " +
                           String::Format("{0:N0}", amount) + "?",
                       "Konfirmasi Penarikan", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::WithdrawSaldo(currentUserID, amount)) {
      MessageBox::Show("Penarikan berhasil!\\n\\nJumlah: Rp " +
                           String::Format("{0:N0}", amount) +
                           "\\n\\nSaldo akan ditransfer ke rekening Anda.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadDashboard();
      txtWithdrawAmount->Text = "";
    } else {
      MessageBox::Show("Gagal melakukan penarikan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void courierForm::btnLogout_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  this->Close();
}

} // namespace ECommerce
