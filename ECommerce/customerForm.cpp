// customerForm.cpp - Implementation of customerForm event handlers
#include "customerForm.h"

namespace ECommerce {

System::Void customerForm::customerForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  LoadSaldo();
  LoadCatalog();
  LoadHistory();
  LoadProfile();
}

void customerForm::LoadCatalog() {
  dgvProducts->DataSource = DatabaseManager::GetAllProductsTable();
}

void customerForm::LoadHistory() {
  dgvHistory->DataSource =
      DatabaseManager::GetTransactionsByCustomer(currentUserID);
}

void customerForm::LoadSaldo() {
  currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblSaldoInfo->Text = L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
  lblCurrentSaldo->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

System::Void customerForm::btnRefreshCatalog_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  LoadCatalog();
  LoadSaldo();
}

System::Void customerForm::btnBuy_Click(System::Object ^ sender,
                                        System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan dibeli!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["ID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  int harga =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["Harga"]->Value);

  // Check saldo
  if (currentSaldo < harga) {
    MessageBox::Show(
        "Saldo tidak cukup! Silakan top up terlebih dahulu.\n\nHarga: Rp " +
            String::Format("{0:N0}", harga) + "\nSaldo Anda: Rp " +
            String::Format("{0:N0}", currentSaldo),
        "Saldo Tidak Cukup", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Apakah Anda yakin ingin membeli '" + productName +
                           "'?\n\nHarga: Rp " + String::Format("{0:N0}", harga),
                       "Konfirmasi Pembelian", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::PurchaseProduct(productID, currentUserID)) {
      MessageBox::Show("Pembelian berhasil!\n\nProduk: " + productName +
                           "\nHarga: Rp " + String::Format("{0:N0}", harga) +
                           "\n\nPesanan Anda akan segera diproses.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadSaldo();
      LoadHistory();
    } else {
      MessageBox::Show("Gagal melakukan pembelian. Pastikan saldo mencukupi!",
                       "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void customerForm::btnRefreshHistory_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  LoadHistory();
}

System::Void customerForm::btnTopUp_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  int amount = 0;
  if (!Int32::TryParse(txtTopUpAmount->Text, amount) || amount <= 0) {
    MessageBox::Show("Masukkan jumlah top up yang valid (angka positif)!",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  if (DatabaseManager::TopUpSaldo(currentUserID, amount)) {
    MessageBox::Show(
        "Top up berhasil!\n\nJumlah: Rp " + String::Format("{0:N0}", amount),
        "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
    LoadSaldo();
  } else {
    MessageBox::Show("Gagal melakukan top up!", "Error", MessageBoxButtons::OK,
                     MessageBoxIcon::Error);
  }
}

System::Void customerForm::btnLogout_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  this->Close();
}

void customerForm::LoadProfile() {
  String ^ alamat = DatabaseManager::GetUserAddress(currentUserID);
  txtAlamat->Text = alamat;
}

System::Void customerForm::btnSaveAlamat_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  String ^ alamat = txtAlamat->Text->Trim();
  
  if (DatabaseManager::UpdateUserAddress(currentUserID, alamat)) {
    MessageBox::Show("Alamat berhasil disimpan!", "Sukses",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
  } else {
    MessageBox::Show("Gagal menyimpan alamat!", "Error",
                     MessageBoxButtons::OK, MessageBoxIcon::Error);
  }
}

} // namespace ECommerce
