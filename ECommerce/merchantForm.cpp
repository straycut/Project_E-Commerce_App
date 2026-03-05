// merchantForm.cpp - Implementation of merchantForm event handlers
#include "merchantForm.h"

namespace ECommerce {

System::Void merchantForm::merchantForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  isEditMode = false;
  editProductID = 0;

  // Apply DGV theming
  array<DataGridView ^> ^ grids = {dgvProducts, dgvSales};
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
    dgv->DefaultCellStyle->WrapMode = DataGridViewTriState::True;
    dgv->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
  }

  LoadDashboard();
  LoadProducts();
  LoadSales();
  LoadProfile();

  // === Dynamic Tab: Notifikasi ===
  tabNotifikasi = gcnew TabPage();
  tabNotifikasi->Text = L"Notifikasi";
  tabNotifikasi->UseVisualStyleBackColor = true;

  dgvNotifikasi = gcnew DataGridView();
  dgvNotifikasi->Location = System::Drawing::Point(10, 15);
  dgvNotifikasi->Size = System::Drawing::Size(832, 420);
  dgvNotifikasi->AllowUserToAddRows = false;
  dgvNotifikasi->AllowUserToDeleteRows = false;
  dgvNotifikasi->ReadOnly = true;
  dgvNotifikasi->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
  dgvNotifikasi->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
  dgvNotifikasi->BackgroundColor = System::Drawing::Color::White;
  dgvNotifikasi->BorderStyle = System::Windows::Forms::BorderStyle::None;
  dgvNotifikasi->EnableHeadersVisualStyles = false;
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->BackColor =
      System::Drawing::Color::FromArgb(46, 125, 50);
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->ForeColor =
      System::Drawing::Color::White;
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->Font =
      gcnew System::Drawing::Font(L"Segoe UI", 10,
                                  System::Drawing::FontStyle::Bold);
  dgvNotifikasi->DefaultCellStyle->Font =
      gcnew System::Drawing::Font(L"Segoe UI", 9);
  dgvNotifikasi->DefaultCellStyle->WrapMode = DataGridViewTriState::True;
  dgvNotifikasi->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
  dgvNotifikasi->ColumnHeadersHeight = 36;
  dgvNotifikasi->RowTemplate->Height = 32;

  tabNotifikasi->Controls->Add(dgvNotifikasi);
  tabControl->Controls->Add(tabNotifikasi);

  LoadNotifikasi();

  // Auto-switch to notification tab if there are unread notifications
  int unreadCount = DatabaseManager::GetUnreadNotificationCount(currentUserID);
  if (unreadCount > 0) {
    tabControl->SelectedTab = tabNotifikasi;
    DatabaseManager::MarkNotificationsRead(currentUserID);
    tabNotifikasi->Text = L"Notifikasi";
  }
}

void merchantForm::LoadDashboard() {
  array<int> ^ stats = DatabaseManager::GetMerchantStats(currentUserID);
  lblTotalProducts->Text = L"Total Produk: " + stats[0];
  lblTotalSales->Text = L"Total Penjualan: " + stats[1];
  lblTotalIncome->Text =
      L"Pendapatan: Rp " + String::Format("{0:N0}", stats[2]);

  // Display current balance
  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblCurrentBalance->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

void merchantForm::LoadProfile() {
  String ^ alamat = DatabaseManager::GetUserAddress(currentUserID);
  txtAlamatToko->Text = alamat;
}

void merchantForm::LoadProducts() {
  dgvProducts->DataSource =
      DatabaseManager::GetProductsByMerchant(currentUserID);
  if (dgvProducts->Columns["_RawID"] != nullptr)
    dgvProducts->Columns["_RawID"]->Visible = false;
}

void merchantForm::LoadSales() {
  dgvSales->DataSource =
      DatabaseManager::GetTransactionsByMerchant(currentUserID);
  if (dgvSales->Columns["_RawID"] != nullptr)
    dgvSales->Columns["_RawID"]->Visible = false;
}

void merchantForm::ClearProductForm() {
  txtNamaProduk->Text = "";
  txtHarga->Text = "";
  txtKomisi->Text = "5";
  txtStok->Text = "0";
  txtKategori->Text = "";
  txtDeskripsi->Text = "";
  isEditMode = false;
  editProductID = 0;
  panelProduct->Visible = false;
}

System::Void merchantForm::btnSaveAlamat_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  String ^ alamat = txtAlamatToko->Text->Trim();

  if (DatabaseManager::UpdateUserAddress(currentUserID, alamat)) {
    MessageBox::Show("Lokasi toko berhasil disimpan!", "Sukses",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
  } else {
    MessageBox::Show("Gagal menyimpan lokasi toko!", "Error",
                     MessageBoxButtons::OK, MessageBoxIcon::Error);
  }
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
  txtStok->Text = "0";
  txtKategori->Text = "";
  txtDeskripsi->Text = "";
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
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  txtNamaProduk->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtHarga->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  // Komisi is fixed at 5%, no need to read from grid
  txtKomisi->Text = "5";
  txtStok->Text =
      dgvProducts->SelectedRows[0]->Cells["Stok"]->Value->ToString();
  txtKategori->Text =
      dgvProducts->SelectedRows[0]->Cells["Kategori"]->Value->ToString();
  txtDeskripsi->Text =
      dgvProducts->SelectedRows[0]->Cells["Deskripsi"]->Value->ToString();
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
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
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
  int komisi = 5; // Fixed 5% commission

  if (!Int32::TryParse(txtHarga->Text, harga) || harga <= 0) {
    MessageBox::Show("Harga harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int stok = 0;
  if (!Int32::TryParse(txtStok->Text, stok) || stok < 0) {
    MessageBox::Show("Stok harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  bool success = false;

  if (isEditMode) {
    success = DatabaseManager::UpdateProduct(
        editProductID, txtNamaProduk->Text, harga, komisi, stok,
        txtKategori->Text, txtDeskripsi->Text);
  } else {
    success = DatabaseManager::AddProduct(
        txtNamaProduk->Text, harga, komisi, stok, currentUserID,
        txtKategori->Text, txtDeskripsi->Text);
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

System::Void merchantForm::btnAddStock_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk untuk menambah stok!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  isEditMode = true;
  editProductID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  txtNamaProduk->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtHarga->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  // Komisi is fixed at 5%, no need to read from grid
  txtKomisi->Text = "5";
  txtStok->Text =
      dgvProducts->SelectedRows[0]->Cells["Stok"]->Value->ToString();
  txtKategori->Text =
      dgvProducts->SelectedRows[0]->Cells["Kategori"]->Value->ToString();
  txtDeskripsi->Text =
      dgvProducts->SelectedRows[0]->Cells["Deskripsi"]->Value->ToString();
  panelProduct->Visible = true;
  txtStok->Focus();
  txtStok->SelectAll();
}

System::Void merchantForm::btnWithdraw_Click(System::Object ^ sender,
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

void merchantForm::LoadNotifikasi() {
  DataTable ^ dt = DatabaseManager::GetNotifications(currentUserID);
  dgvNotifikasi->DataSource = dt;

  int unread = DatabaseManager::GetUnreadNotificationCount(currentUserID);
  if (unread > 0) {
    tabNotifikasi->Text = L"Notifikasi (" + unread + L")";
  } else {
    tabNotifikasi->Text = L"Notifikasi";
  }
}

} // namespace ECommerce
