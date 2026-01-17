// merchantForm.cpp - Implementation of merchantForm event handlers
#include "merchantForm.h"

namespace ECommerce {

System::Void merchantForm::merchantForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  isEditMode = false;
  editProductID = 0;
  LoadDashboard();
  LoadProducts();
  LoadSales();
}

void merchantForm::LoadDashboard() {
  array<int> ^ stats = DatabaseManager::GetMerchantStats(currentUserID);
  lblTotalProducts->Text = L"Total Produk: " + stats[0];
  lblTotalSales->Text = L"Total Penjualan: " + stats[1];
  lblTotalIncome->Text =
      L"Pendapatan: Rp " + String::Format("{0:N0}", stats[2]);
}

void merchantForm::LoadProducts() {
  dgvProducts->DataSource =
      DatabaseManager::GetProductsByMerchant(currentUserID);
}

void merchantForm::LoadSales() {
  dgvSales->DataSource =
      DatabaseManager::GetTransactionsByMerchant(currentUserID);
}

void merchantForm::ClearProductForm() {
  txtNamaProduk->Text = "";
  txtHarga->Text = "";
  txtKomisi->Text = "5";
  isEditMode = false;
  editProductID = 0;
  panelProduct->Visible = false;
}

System::Void merchantForm::btnRefreshDashboard_Click(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  LoadDashboard();
  MessageBox::Show("Dashboard diperbarui!", "Info", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
}

System::Void merchantForm::btnRefreshProducts_Click(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  LoadProducts();
}

System::Void merchantForm::btnAddProduct_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  isEditMode = false;
  editProductID = 0;
  txtNamaProduk->Text = "";
  txtHarga->Text = "";
  txtKomisi->Text = "5";
  panelProduct->Visible = true;
  txtNamaProduk->Focus();
}

System::Void merchantForm::btnEditProduct_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan diedit!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  isEditMode = true;
  editProductID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["ID"]->Value);
  txtNamaProduk->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtHarga->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  txtKomisi->Text =
      dgvProducts->SelectedRows[0]->Cells["Komisi"]->Value->ToString();
  panelProduct->Visible = true;
  txtNamaProduk->Focus();
}

System::Void merchantForm::btnDeleteProduct_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan dihapus!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["ID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();

  if (MessageBox::Show("Apakah Anda yakin ingin menghapus produk '" +
                           productName + "'?",
                       "Konfirmasi Hapus", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::DeleteProduct(productID)) {
      MessageBox::Show("Produk berhasil dihapus!", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadProducts();
      LoadDashboard();
    } else {
      MessageBox::Show("Gagal menghapus produk!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void merchantForm::btnSaveProduct_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  // Validasi input
  if (String::IsNullOrWhiteSpace(txtNamaProduk->Text)) {
    MessageBox::Show("Nama produk tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int harga = 0;
  int komisi = 0;

  if (!Int32::TryParse(txtHarga->Text, harga) || harga <= 0) {
    MessageBox::Show("Harga harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (!Int32::TryParse(txtKomisi->Text, komisi) || komisi < 0 || komisi > 100) {
    MessageBox::Show("Komisi harus berupa angka antara 0-100!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  bool success = false;

  if (isEditMode) {
    success = DatabaseManager::UpdateProduct(editProductID, txtNamaProduk->Text,
                                             harga, komisi);
  } else {
    success = DatabaseManager::AddProduct(txtNamaProduk->Text, harga, komisi,
                                          currentUserID);
  }

  if (success) {
    MessageBox::Show(isEditMode ? "Produk berhasil diperbarui!"
                                : "Produk berhasil ditambahkan!",
                     "Sukses", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    ClearProductForm();
    LoadProducts();
    LoadDashboard();
  } else {
    MessageBox::Show("Gagal menyimpan produk!", "Error", MessageBoxButtons::OK,
                     MessageBoxIcon::Error);
  }
}

System::Void merchantForm::btnCancelProduct_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  ClearProductForm();
}

System::Void merchantForm::btnRefreshSales_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  LoadSales();
}

System::Void merchantForm::btnLogout_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  this->Close();
}

} // namespace ECommerce
