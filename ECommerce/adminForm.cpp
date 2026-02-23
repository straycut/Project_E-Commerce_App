// adminForm.cpp - Implementation of adminForm event handlers
#include "adminForm.h"

namespace ECommerce {

System::Void adminForm::adminForm_Load(System::Object ^ sender,
                                       System::EventArgs ^ e) {
  // Apply DGV theming
  array<DataGridView ^> ^
      grids = {dgvUsers, dgvIncome, dgvTransactions, dgvProducts};
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

  LoadDashboardStats();
  LoadUsers();
  LoadIncome();
  LoadTransactions();
  LoadProducts();
  editProductID = 0;
}

void adminForm::LoadDashboardStats() {
  array<int> ^ stats = DatabaseManager::GetDashboardStats();
  lblTotalUsers->Text = L"Total Users: " + stats[0];
  lblTotalMerchants->Text = L"Merchants: " + stats[1];
  lblTotalCustomers->Text = L"Customers: " + stats[2];
  lblTotalCouriers->Text = L"Couriers: " + stats[3];
  lblTotalTransactions->Text = L"Total Transactions: " + stats[4];
  lblActiveUsers->Text = L"Active Users: " + stats[6];
  lblInactiveUsers->Text = L"Inactive Users: " + stats[7];

  // Get income breakdown by type
  array<int> ^ income = DatabaseManager::GetIncomeBreakdown();
  lblTotalIncome->Text =
      L"Total Income: Rp " + String::Format("{0:N0}", income[0]);
  lblAppIncome->Text = L"Aplikasi: Rp " + String::Format("{0:N0}", income[1]);
  lblMerchantIncome->Text =
      L"Merchant: Rp " + String::Format("{0:N0}", income[2]);
  lblCourierIncome->Text =
      L"Courier: Rp " + String::Format("{0:N0}", income[3]);

  // Update admin saldo display
  int adminSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblAdminWithdrawLabel->Text =
      L"Tarik Saldo (Saldo: Rp " + String::Format("{0:N0}", adminSaldo) + L"):";
}

void adminForm::LoadUsers() { FilterUsers(); }

void adminForm::FilterUsers() {
  DataTable ^ dt = DatabaseManager::GetAllUsersTable();

  // Apply filter - check if controls are initialized
  String ^ searchText =
      txtSearchUser != nullptr ? txtSearchUser->Text->Trim()->ToLower() : "";
  String ^ selectedRole =
      (cmbFilterRole != nullptr && cmbFilterRole->SelectedItem != nullptr)
          ? cmbFilterRole->SelectedItem->ToString()
          : "Semua";

  // Create filtered view
  DataTable ^ filteredDt = dt->Clone();

  for each (DataRow ^ row in dt->Rows) {
    String ^ username = row["Username"]->ToString()->ToLower();
    String ^ role = row["Role"]->ToString();

    bool matchSearch =
        String::IsNullOrEmpty(searchText) || username->Contains(searchText);
    bool matchRole = selectedRole == "Semua" || role == selectedRole;

    if (matchSearch && matchRole) {
      filteredDt->ImportRow(row);
    }
  }

  dgvUsers->DataSource = filteredDt;
  if (dgvUsers->Columns["_RawID"] != nullptr)
    dgvUsers->Columns["_RawID"]->Visible = false;
  if (dgvUsers->Columns["_Password"] != nullptr)
    dgvUsers->Columns["_Password"]->Visible = false;
}

System::Void adminForm::txtSearchUser_TextChanged(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  FilterUsers();
}

System::Void
adminForm::cmbFilterRole_SelectedIndexChanged(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  FilterUsers();
}

void adminForm::LoadIncome() { FilterIncome(); }

void adminForm::FilterIncome() {
  DataTable ^ dt = DatabaseManager::GetAllIncomeTable();

  // Read filter values
  String ^ selectedType =
      (cmbFilterType != nullptr && cmbFilterType->SelectedItem != nullptr)
          ? cmbFilterType->SelectedItem->ToString()
          : "Semua";
  String ^ searchText = txtSearchIncome != nullptr
                            ? txtSearchIncome->Text->Trim()->ToLower()
                            : "";

  bool hasFilter =
      (selectedType != "Semua") || !String::IsNullOrEmpty(searchText);

  DataTable ^ displayDt = hasFilter ? dt->Clone() : dt;

  if (hasFilter) {
    for each (DataRow ^ row in dt->Rows) {
      String ^ type = row["Type"]->ToString();
      String ^ username = row["Username"]->ToString()->ToLower();
      String ^ desc = row["Description"]->ToString()->ToLower();
      String ^ id = row["ID"]->ToString()->ToLower();

      bool matchType = selectedType == "Semua" || type == selectedType;
      bool matchSearch = String::IsNullOrEmpty(searchText) ||
                         username->Contains(searchText) ||
                         desc->Contains(searchText) || id->Contains(searchText);

      if (matchType && matchSearch)
        displayDt->ImportRow(row);
    }
  }

  dgvIncome->DataSource = displayDt;
  if (dgvIncome->Columns["_RawID"] != nullptr)
    dgvIncome->Columns["_RawID"]->Visible = false;

  // Calculate total from full dataset (not filtered)
  int total = 0;
  for each (DataRow ^ row in dt->Rows) {
    total += Convert::ToInt32(row["Amount"]);
  }
  lblTotalIncomeValue->Text = L"Total: Rp " + String::Format("{0:N0}", total);
}

void adminForm::LoadTransactions() { FilterTransactions(); }

void adminForm::FilterTransactions() {
  DataTable ^ dt = DatabaseManager::GetAllTransactionsTable();

  // Check if controls are initialized
  String ^ selectedStatus =
      (cmbFilterStatus != nullptr && cmbFilterStatus->SelectedItem != nullptr)
          ? cmbFilterStatus->SelectedItem->ToString()
          : "Semua";
  String ^ searchText = txtSearchTransaction != nullptr
                            ? txtSearchTransaction->Text->Trim()->ToLower()
                            : "";

  bool hasFilter =
      (selectedStatus != "Semua") || !String::IsNullOrEmpty(searchText);

  if (!hasFilter) {
    dgvTransactions->DataSource = dt;
    if (dgvTransactions->Columns["_RawID"] != nullptr)
      dgvTransactions->Columns["_RawID"]->Visible = false;
    return;
  }

  // Create filtered view
  DataTable ^ filteredDt = dt->Clone();

  for each (DataRow ^ row in dt->Rows) {
    String ^ status = row["Status"]->ToString();
    String ^ pembeli = row["Pembeli"]->ToString()->ToLower();
    String ^ kurir = row["Kurir"]->ToString()->ToLower();
    String ^ id = row["ID"]->ToString()->ToLower();

    bool matchStatus = selectedStatus == "Semua" || status == selectedStatus;
    bool matchSearch = String::IsNullOrEmpty(searchText) ||
                       pembeli->Contains(searchText) ||
                       kurir->Contains(searchText) || id->Contains(searchText);

    if (matchStatus && matchSearch) {
      filteredDt->ImportRow(row);
    }
  }

  dgvTransactions->DataSource = filteredDt;
  if (dgvTransactions->Columns["_RawID"] != nullptr)
    dgvTransactions->Columns["_RawID"]->Visible = false;
}

System::Void
adminForm::cmbFilterStatus_SelectedIndexChanged(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  FilterTransactions();
}

System::Void
adminForm::txtSearchTransaction_TextChanged(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  FilterTransactions();
}

System::Void adminForm::btnRefreshStats_Click(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  LoadDashboardStats();
  MessageBox::Show("Dashboard refreshed!", "Info", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
}

System::Void adminForm::btnRefreshUsers_Click(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  LoadUsers();
}

System::Void adminForm::btnActivateUser_Click(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  if (dgvUsers->SelectedRows->Count == 0) {
    MessageBox::Show("Please select a user first!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int userID =
      Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ role = dgvUsers->SelectedRows[0]->Cells["Role"]->Value->ToString();

  if (role == "Admin") {
    MessageBox::Show("Cannot modify Admin account!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (DatabaseManager::SetUserActive(userID, true)) {
    MessageBox::Show("User activated successfully!", "Success",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
    LoadUsers();
    LoadDashboardStats();
  }
}

System::Void adminForm::btnDeactivateUser_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  if (dgvUsers->SelectedRows->Count == 0) {
    MessageBox::Show("Please select a user first!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int userID =
      Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ username =
      dgvUsers->SelectedRows[0]->Cells["Username"]->Value->ToString();
  String ^ role = dgvUsers->SelectedRows[0]->Cells["Role"]->Value->ToString();

  if (role == "Admin") {
    MessageBox::Show("Cannot deactivate Admin account!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Are you sure you want to deactivate user '" + username +
                           "'?",
                       "Confirm Deactivation", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::SetUserActive(userID, false)) {
      MessageBox::Show("User deactivated successfully!", "Success",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadUsers();
      LoadDashboardStats();
    }
  }
}

System::Void adminForm::btnDeleteUser_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  if (dgvUsers->SelectedRows->Count == 0) {
    MessageBox::Show("Please select a user first!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int userID =
      Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ username =
      dgvUsers->SelectedRows[0]->Cells["Username"]->Value->ToString();
  String ^ role = dgvUsers->SelectedRows[0]->Cells["Role"]->Value->ToString();

  if (userID == currentUserID) {
    MessageBox::Show("Tidak dapat menghapus akun Anda sendiri!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (role == "Admin") {
    MessageBox::Show(
        "Akun Admin tidak dapat dihapus untuk menjaga integritas data "
        "income.\nGunakan 'Nonaktifkan User' sebagai gantinya.",
        "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Are you sure you want to PERMANENTLY DELETE user '" +
                           username + "'?\n\nThis action cannot be undone!",
                       "Confirm Delete", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Warning) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::DeleteUser(userID)) {
      MessageBox::Show("User deleted successfully!", "Success",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadUsers();
      LoadDashboardStats();
    }
  }
}

System::Void adminForm::btnRefreshIncome_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  LoadIncome();
}

System::Void adminForm::txtSearchIncome_TextChanged(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  FilterIncome();
}

System::Void
adminForm::cmbFilterType_SelectedIndexChanged(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  FilterIncome();
}

System::Void adminForm::btnRefreshTransactions_Click(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  LoadTransactions();
}

System::Void adminForm::btnLogout_Click(System::Object ^ sender,
                                        System::EventArgs ^ e) {
  this->Close();
}

System::Void adminForm::tabDashboard_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  // Empty handler
}

System::Void adminForm::btnAddUser_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
  ClearAddUserForm();
  editingUserID = -1;
  cmbNewRole->Enabled = true;
  lblPanelTitle->Text = L"Tambah User";
  panelAddUser->Visible = true;
  panelAddUser->BringToFront();
  txtNewUsername->Focus();
}

System::Void adminForm::btnSaveUser_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  // Validate input
  String ^ username = txtNewUsername->Text->Trim();
  String ^ password = txtNewPassword->Text;

  if (String::IsNullOrEmpty(username)) {
    MessageBox::Show("Username tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (editingUserID > 0) {
    // EDIT MODE
    if (DatabaseManager::UpdateUser(editingUserID, username, password)) {
      MessageBox::Show("User berhasil diupdate!", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      ClearAddUserForm();
      panelAddUser->Visible = false;
      editingUserID = -1;
      cmbNewRole->Enabled = true;
      FilterUsers();
    } else {
      MessageBox::Show("Gagal mengupdate user!", "Error", MessageBoxButtons::OK,
                       MessageBoxIcon::Error);
    }
  } else {
    // ADD MODE
    if (String::IsNullOrEmpty(password)) {
      MessageBox::Show("Password tidak boleh kosong!", "Peringatan",
                       MessageBoxButtons::OK, MessageBoxIcon::Warning);
      return;
    }

    if (cmbNewRole->SelectedIndex < 0) {
      MessageBox::Show("Pilih role untuk user!", "Peringatan",
                       MessageBoxButtons::OK, MessageBoxIcon::Warning);
      return;
    }

    String ^ role = cmbNewRole->SelectedItem->ToString();

    // Register user
    if (DatabaseManager::RegisterUser(username, password, role)) {
      MessageBox::Show("User berhasil ditambahkan!", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      ClearAddUserForm();
      panelAddUser->Visible = false;
      LoadUsers();
      LoadDashboardStats();
    } else {
      MessageBox::Show("Gagal menambahkan user! Username mungkin sudah ada.",
                       "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void adminForm::btnCancelAddUser_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  ClearAddUserForm();
  panelAddUser->Visible = false;
  editingUserID = -1;
  cmbNewRole->Enabled = true;
}

void adminForm::ClearAddUserForm() {
  txtNewUsername->Text = "";
  txtNewPassword->Text = "";
  txtNewPassword->PasswordChar = '*';
  cmbNewRole->SelectedIndex = -1;
}

System::Void adminForm::btnEditUser_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  if (dgvUsers->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih user yang akan diedit!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  editingUserID =
      Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ currentUsername =
      dgvUsers->SelectedRows[0]->Cells["Username"]->Value->ToString();
  String ^ currentPassword =
      dgvUsers->SelectedRows[0]->Cells["_Password"]->Value->ToString();
  String ^ currentRole =
      dgvUsers->SelectedRows[0]->Cells["Role"]->Value->ToString();

  // Pre-fill the panel
  txtNewUsername->Text = currentUsername;
  txtNewPassword->Text = currentPassword;
  txtNewPassword->PasswordChar = '\0'; // Show password text

  // Set role and disable it (can't change role during edit)
  for (int i = 0; i < cmbNewRole->Items->Count; i++) {
    if (cmbNewRole->Items[i]->ToString() == currentRole) {
      cmbNewRole->SelectedIndex = i;
      break;
    }
  }
  cmbNewRole->Enabled = false;
  lblPanelTitle->Text = L"Edit User";

  panelAddUser->Visible = true;
  panelAddUser->BringToFront();
  txtNewUsername->Focus();
}

// Products management
void adminForm::LoadProducts() { FilterProducts(); }

void adminForm::FilterProducts() {
  DataTable ^ dt = DatabaseManager::GetAllProductsTable();

  String ^ searchText = txtSearchProduct != nullptr
                            ? txtSearchProduct->Text->Trim()->ToLower()
                            : "";

  if (String::IsNullOrEmpty(searchText)) {
    dgvProducts->DataSource = dt;
    if (dgvProducts->Columns["_RawID"] != nullptr)
      dgvProducts->Columns["_RawID"]->Visible = false;
    return;
  }

  DataTable ^ filteredDt = dt->Clone();

  for each (DataRow ^ row in dt->Rows) {
    String ^ nama = row["Nama"]->ToString()->ToLower();
    String ^ kategori = row["Kategori"]->ToString()->ToLower();
    String ^ id = row["ID"]->ToString()->ToLower();

    if (nama->Contains(searchText) || kategori->Contains(searchText) ||
        id->Contains(searchText)) {
      filteredDt->ImportRow(row);
    }
  }

  dgvProducts->DataSource = filteredDt;
  if (dgvProducts->Columns["_RawID"] != nullptr)
    dgvProducts->Columns["_RawID"]->Visible = false;
}

System::Void adminForm::txtSearchProduct_TextChanged(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  FilterProducts();
}

System::Void adminForm::btnRefreshProducts_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  LoadProducts();
}

System::Void adminForm::btnEditProduct_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan diedit!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  editProductID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  txtEditProductName->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtEditProductPrice->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  txtEditProductStock->Text =
      dgvProducts->SelectedRows[0]->Cells["Stok"]->Value->ToString();
  txtEditProductKategori->Text =
      dgvProducts->SelectedRows[0]->Cells["Kategori"]->Value->ToString();
  txtEditProductDeskripsi->Text =
      dgvProducts->SelectedRows[0]->Cells["Deskripsi"]->Value->ToString();

  panelEditProduct->Visible = true;
  panelEditProduct->BringToFront();
  txtEditProductName->Focus();
}

System::Void adminForm::btnDeleteProduct_Click(System::Object ^ sender,
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
      LoadDashboardStats();
    } else {
      MessageBox::Show("Gagal menghapus produk!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void adminForm::btnSaveProduct_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (String::IsNullOrWhiteSpace(txtEditProductName->Text)) {
    MessageBox::Show("Nama produk tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int harga = 0;
  int stok = 0;
  int komisi = 5; // Fixed 5% commission

  if (!Int32::TryParse(txtEditProductPrice->Text, harga) || harga <= 0) {
    MessageBox::Show("Harga harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (!Int32::TryParse(txtEditProductStock->Text, stok) || stok < 0) {
    MessageBox::Show("Stok harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (DatabaseManager::UpdateProduct(
          editProductID, txtEditProductName->Text, harga, komisi, stok,
          txtEditProductKategori->Text, txtEditProductDeskripsi->Text)) {
    MessageBox::Show("Produk berhasil diperbarui!", "Sukses",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
    ClearEditProductForm();
    panelEditProduct->Visible = false;
    LoadProducts();
  } else {
    MessageBox::Show("Gagal memperbarui produk!", "Error",
                     MessageBoxButtons::OK, MessageBoxIcon::Error);
  }
}

System::Void adminForm::btnCancelEditProduct_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  ClearEditProductForm();
  panelEditProduct->Visible = false;
}

void adminForm::ClearEditProductForm() {
  txtEditProductName->Text = "";
  txtEditProductPrice->Text = "";
  txtEditProductStock->Text = "";
  txtEditProductKategori->Text = "";
  txtEditProductDeskripsi->Text = "";
  editProductID = 0;
}

// Transaction status edit
System::Void adminForm::btnEditTransactionStatus_Click(System::Object ^ sender,
                                                       System::EventArgs ^ e) {
  if (dgvTransactions->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih transaksi yang akan diubah statusnya!",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  int transID = Convert::ToInt32(
      dgvTransactions->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ currentStatus =
      dgvTransactions->SelectedRows[0]->Cells["Status"]->Value->ToString();

  // Create a simple form for status selection
  System::Windows::Forms::Form ^ dialog = gcnew System::Windows::Forms::Form();
  dialog->Text = "Ubah Status Transaksi";
  dialog->Size = System::Drawing::Size(300, 200);
  dialog->StartPosition = FormStartPosition::CenterParent;
  dialog->FormBorderStyle =
      System::Windows::Forms::FormBorderStyle::FixedDialog;
  dialog->MaximizeBox = false;
  dialog->MinimizeBox = false;

  Label ^ lblInfo = gcnew Label();
  lblInfo->Text = "Status saat ini: " + currentStatus + "\nPilih status baru:";
  lblInfo->Location = System::Drawing::Point(15, 15);
  lblInfo->Size = System::Drawing::Size(250, 35);
  dialog->Controls->Add(lblInfo);

  ComboBox ^ cmbStatus = gcnew ComboBox();
  cmbStatus->DropDownStyle = ComboBoxStyle::DropDownList;
  cmbStatus->Items->AddRange(gcnew array<Object ^>(4){
      "pending", "shipping", "delivered", "cancelled"});
  cmbStatus->Location = System::Drawing::Point(15, 55);
  cmbStatus->Size = System::Drawing::Size(250, 21);
  dialog->Controls->Add(cmbStatus);

  Button ^ btnOK = gcnew Button();
  btnOK->Text = "Simpan";
  btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
  btnOK->Location = System::Drawing::Point(15, 100);
  btnOK->Size = System::Drawing::Size(100, 30);
  dialog->Controls->Add(btnOK);

  Button ^ btnCancel = gcnew Button();
  btnCancel->Text = "Batal";
  btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  btnCancel->Location = System::Drawing::Point(130, 100);
  btnCancel->Size = System::Drawing::Size(100, 30);
  dialog->Controls->Add(btnCancel);

  dialog->AcceptButton = btnOK;
  dialog->CancelButton = btnCancel;

  if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
    if (cmbStatus->SelectedIndex >= 0) {
      String ^ newStatus = cmbStatus->SelectedItem->ToString();

      if (DatabaseManager::UpdateTransactionStatus(transID, newStatus)) {
        MessageBox::Show(
            "Status transaksi berhasil diubah menjadi '" + newStatus + "'!",
            "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
        LoadTransactions();
      } else {
        MessageBox::Show("Gagal mengubah status transaksi!", "Error",
                         MessageBoxButtons::OK, MessageBoxIcon::Error);
      }
    }
  }
}

// Delete transaction
System::Void adminForm::btnDeleteTransaction_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  if (dgvTransactions->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih transaksi yang akan dihapus!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transID = Convert::ToInt32(
      dgvTransactions->SelectedRows[0]->Cells["_RawID"]->Value);

  System::Windows::Forms::DialogResult result = MessageBox::Show(
      "Apakah Anda yakin ingin menghapus transaksi ID: " + transID + "?",
      "Konfirmasi Hapus", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

  if (result == System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::DeleteTransaction(transID)) {
      MessageBox::Show("Transaksi berhasil dihapus!", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadTransactions();
    } else {
      MessageBox::Show("Gagal menghapus transaksi!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void adminForm::btnAdminWithdraw_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  int amount = 0;
  if (!Int32::TryParse(txtAdminWithdrawAmount->Text, amount) || amount <= 0) {
    MessageBox::Show("Masukkan jumlah penarikan yang valid!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  if (amount > currentSaldo) {
    MessageBox::Show("Saldo tidak mencukupi!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Tarik saldo sebesar Rp " +
                           String::Format("{0:N0}", amount) + "?",
                       "Konfirmasi Penarikan", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::WithdrawSaldo(currentUserID, amount)) {
      MessageBox::Show("Penarikan berhasil!", "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      txtAdminWithdrawAmount->Text = "";
      LoadDashboardStats();
    } else {
      MessageBox::Show("Gagal melakukan penarikan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

} // namespace ECommerce
