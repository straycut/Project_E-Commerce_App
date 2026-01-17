// courierForm.cpp - Implementation of courierForm event handlers
#include "courierForm.h"

namespace ECommerce {

System::Void courierForm::courierForm_Load(System::Object ^ sender,
                                           System::EventArgs ^ e) {
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

  int transID =
      Convert::ToInt32(dgvPending->SelectedRows[0]->Cells["ID"]->Value);

  if (MessageBox::Show("Apakah Anda yakin ingin mengambil pesanan ini?",
                       "Konfirmasi", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::ClaimDelivery(transID, currentUserID)) {
      MessageBox::Show(
          "Pesanan berhasil diambil!\n\nSilakan segera kirim ke customer.",
          "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadPending();
      LoadActive();
      LoadDashboard();
    } else {
      MessageBox::Show(
          "Gagal mengambil pesanan. Mungkin sudah diambil kurir lain.", "Error",
          MessageBoxButtons::OK, MessageBoxIcon::Error);
      LoadPending();
    }
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

  int transID =
      Convert::ToInt32(dgvActive->SelectedRows[0]->Cells["ID"]->Value);

  if (MessageBox::Show("Apakah pengiriman ini sudah selesai?\n\nAnda akan "
                       "menerima ongkos kirim Rp 10.000",
                       "Konfirmasi", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::CompleteDelivery(transID, currentUserID)) {
      MessageBox::Show("Pengiriman selesai!\n\nOnkgos kirim Rp 10.000 telah "
                       "ditambahkan ke saldo Anda.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadActive();
      LoadHistory();
      LoadDashboard();
    } else {
      MessageBox::Show("Gagal menyelesaikan pengiriman!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void courierForm::btnRefreshHistory_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  LoadHistory();
}

System::Void courierForm::btnLogout_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  this->Close();
}

} // namespace ECommerce
