// adminForm.cpp - Implementation of adminForm event handlers
#include "adminForm.h"

namespace ECommerce {

System::Void adminForm::adminForm_Load(System::Object ^ sender,
                                       System::EventArgs ^ e) {
  // Apply DGV theming
  array<DataGridView ^> ^ grids = {dgvUsers, dgvProducts, dgvFrequentProducts};
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
adminForm::TransactionRadioButton_CheckedChanged(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  RadioButton ^ rb = safe_cast<RadioButton ^>(sender);
  if (rb->Checked) {
    for each (Control ^ card in flpTransactions->Controls) {
      if (card->GetType() == Panel::typeid) {
        for each (Control ^ inner in card->Controls) {
          if (inner->GetType() == Panel::typeid) {
            for each (Control ^ ctrl in inner->Controls) {
              if (ctrl->GetType() == RadioButton::typeid && ctrl != rb) {
                safe_cast<RadioButton ^>(ctrl)->Checked = false;
              }
            }
          }
        }
      }
    }
  }
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

  // Map combobox display name to actual DB type value
  String ^ dbType = "Semua";
  if (selectedType == "Aplikasi")
    dbType = "commission";
  else if (selectedType == "Merchant")
    dbType = "sale";
  else if (selectedType == "Courier")
    dbType = "delivery";
  else if (selectedType == "Withdrawal")
    dbType = "withdrawal";

  bool hasFilter = (dbType != "Semua") || !String::IsNullOrEmpty(searchText);
  DataTable ^ displayDt = hasFilter ? dt->Clone() : dt;

  if (hasFilter) {
    for each (DataRow ^ row in dt->Rows) {
      String ^ type = row["Type"]->ToString();
      String ^ username = row["Username"]->ToString()->ToLower();
      String ^ desc = row["Description"]->ToString()->ToLower();
      String ^ id = row["ID"]->ToString()->ToLower();

      bool matchType = dbType == "Semua" || type == dbType;
      bool matchSearch = String::IsNullOrEmpty(searchText) ||
                         username->Contains(searchText) ||
                         desc->Contains(searchText) || id->Contains(searchText);

      if (matchType && matchSearch)
        displayDt->ImportRow(row);
    }
  } else {
    displayDt = dt;
  }

  // Calculate total from full dataset (not filtered)
  int total = 0;
  for each (DataRow ^ row in dt->Rows) {
    total += Convert::ToInt32(row["Amount"]);
  }
  lblTotalIncomeValue->Text = L"Total: Rp " + String::Format("{0:N0}", total);

  // Render to FlowLayoutPanel (Grouped by Username)
  flpIncome->Controls->Clear();

  if (displayDt->Rows->Count == 0) {
    Label ^ lblEmpty = gcnew Label();
    lblEmpty->Text = L"Tidak ada data income ditemukan.";
    lblEmpty->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
    lblEmpty->ForeColor = System::Drawing::Color::Gray;
    lblEmpty->AutoSize = true;
    lblEmpty->Padding = System::Windows::Forms::Padding(10, 20, 0, 0);
    flpIncome->Controls->Add(lblEmpty);
    return;
  }

  int cardWidth = flpIncome->Width - 30;

  // Group by Username preserving order
  System::Collections::Generic::Dictionary<
      String ^, System::Collections::Generic::List<int> ^> ^
      groups =
      gcnew System::Collections::Generic::Dictionary<
          String ^, System::Collections::Generic::List<int> ^>();
  System::Collections::Generic::List<String ^> ^ groupOrder =
      gcnew System::Collections::Generic::List<String ^>();

  for (int i = 0; i < displayDt->Rows->Count; i++) {
    String ^ username = displayDt->Rows[i]["Username"]->ToString();
    if (!groups->ContainsKey(username)) {
      groups[username] = gcnew System::Collections::Generic::List<int>();
      groupOrder->Add(username);
    }
    groups[username]->Add(i);
  }

  for (int g = 0; g < groupOrder->Count; g++) {
    String ^ username = groupOrder[g];
    System::Collections::Generic::List<int> ^ rowIndices = groups[username];
    int itemCount = rowIndices->Count;

    // Calculate subtotal
    int userTotal = 0;
    for (int r = 0; r < rowIndices->Count; r++) {
      userTotal += Convert::ToInt32(displayDt->Rows[rowIndices[r]]["Amount"]);
    }

    // === Card Panel ===
    Panel ^ card = gcnew Panel();
    card->Width = cardWidth;
    card->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    card->BackColor = System::Drawing::Color::White;
    card->Margin = System::Windows::Forms::Padding(3, 3, 3, 8);

    int yPos = 0;

    // === Header bar ===
    Panel ^ header = gcnew Panel();
    header->Dock = DockStyle::Top;
    header->Height = 42;
    header->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);

    Label ^ lblUser = gcnew Label();
    lblUser->Text = L"User: " + username + L" (" + itemCount + L" record)";
    lblUser->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold);
    lblUser->ForeColor = System::Drawing::Color::White;
    lblUser->Location = System::Drawing::Point(10, 12);
    lblUser->AutoSize = true;
    header->Controls->Add(lblUser);

    card->Controls->Add(header);
    yPos = 48;

    // === Item rows ===
    for (int r = 0; r < rowIndices->Count; r++) {
      int idx = rowIndices[r];
      String ^ date = displayDt->Rows[idx]["Date"]->ToString();
      String ^ desc = displayDt->Rows[idx]["Description"]->ToString();
      int amount = Convert::ToInt32(displayDt->Rows[idx]["Amount"]);
      String ^ type = displayDt->Rows[idx]["Type"]->ToString();

      Panel ^ itemRow = gcnew Panel();
      itemRow->Location = System::Drawing::Point(0, yPos);
      itemRow->Size = System::Drawing::Size(cardWidth - 2, 26);
      if (r % 2 == 1)
        itemRow->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);

      Label ^ lblItem = gcnew Label();
      lblItem->Text = L"  \x2022 [" + date + L"] " + desc;
      lblItem->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblItem->Location = System::Drawing::Point(8, 4);
      lblItem->AutoSize = true;
      itemRow->Controls->Add(lblItem);

      String ^ sign = (type == "withdrawal") ? L"-" : L"+";
      Label ^ lblAmount = gcnew Label();
      lblAmount->Text = sign + L"Rp " + String::Format("{0:N0}", amount);
      lblAmount->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblAmount->ForeColor =
          (type == "withdrawal")
              ? System::Drawing::Color::Red
              : System::Drawing::Color::FromArgb(46, 125, 50);
      lblAmount->Location = System::Drawing::Point(cardWidth - 160, 4);
      lblAmount->AutoSize = true;
      itemRow->Controls->Add(lblAmount);

      card->Controls->Add(itemRow);
      yPos += 26;
    }

    // === Footer ===
    Panel ^ footer = gcnew Panel();
    footer->Location = System::Drawing::Point(0, yPos);
    footer->Size = System::Drawing::Size(cardWidth - 2, 40);
    footer->BackColor = System::Drawing::Color::FromArgb(245, 245, 245);

    Label ^ lblSubtotal = gcnew Label();
    lblSubtotal->Text = L"Subtotal: Rp " + String::Format("{0:N0}", userTotal);
    lblSubtotal->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
    lblSubtotal->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
    lblSubtotal->Location = System::Drawing::Point(10, 10);
    lblSubtotal->AutoSize = true;
    footer->Controls->Add(lblSubtotal);

    card->Controls->Add(footer);
    yPos += 40;

    card->Height = yPos;
    flpIncome->Controls->Add(card);
  }
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

  DataTable ^ displayDt = hasFilter ? dt->Clone() : dt;

  if (hasFilter) {
    for each (DataRow ^ row in dt->Rows) {
      String ^ status = row["Status"]->ToString();
      String ^ pembeli = row["Pembeli"]->ToString()->ToLower();
      String ^ kurir = row["Kurir"]->ToString()->ToLower();
      String ^ id = row["ID"]->ToString()->ToLower();

      bool matchStatus = selectedStatus == "Semua" || status == selectedStatus;
      bool matchSearch =
          String::IsNullOrEmpty(searchText) || pembeli->Contains(searchText) ||
          kurir->Contains(searchText) || id->Contains(searchText);

      if (matchStatus && matchSearch) {
        displayDt->ImportRow(row);
      }
    }
  } else {
    displayDt = dt;
  }

  // Group by Pembeli (customer name)
  flpTransactions->Controls->Clear();

  if (displayDt->Rows->Count == 0) {
    Label ^ lblEmpty = gcnew Label();
    lblEmpty->Text = L"Tidak ada transaksi ditemukan.";
    lblEmpty->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
    lblEmpty->ForeColor = System::Drawing::Color::Gray;
    lblEmpty->AutoSize = true;
    lblEmpty->Padding = System::Windows::Forms::Padding(10, 20, 0, 0);
    flpTransactions->Controls->Add(lblEmpty);
    return;
  }

  int cardWidth = flpTransactions->Width - 30;

  // Group by Pembeli
  System::Collections::Generic::Dictionary<
      String ^, System::Collections::Generic::List<int> ^> ^
      groups =
      gcnew System::Collections::Generic::Dictionary<
          String ^, System::Collections::Generic::List<int> ^>();
  System::Collections::Generic::List<String ^> ^ groupOrder =
      gcnew System::Collections::Generic::List<String ^>();

  for (int i = 0; i < displayDt->Rows->Count; i++) {
    String ^ customer = displayDt->Rows[i]["Pembeli"]->ToString();
    if (!groups->ContainsKey(customer)) {
      groups[customer] = gcnew System::Collections::Generic::List<int>();
      groupOrder->Add(customer);
    }
    groups[customer]->Add(i);
  }

  for (int g = 0; g < groupOrder->Count; g++) {
    String ^ customer = groupOrder[g];
    System::Collections::Generic::List<int> ^ rowIndices = groups[customer];
    int itemCount = rowIndices->Count;

    // === Card Panel ===
    Panel ^ card = gcnew Panel();
    card->Width = cardWidth;
    card->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    card->BackColor = System::Drawing::Color::White;
    card->Margin = System::Windows::Forms::Padding(3, 3, 3, 8);

    int yPos = 0;

    // Build comma-separated IDs for group selection
    String ^ allIDs = "";
    String ^ firstStatus = displayDt->Rows[rowIndices[0]]["Status"]->ToString();
    String ^ firstCourier = displayDt->Rows[rowIndices[0]]["Kurir"]->ToString();
    for (int r = 0; r < rowIndices->Count; r++) {
      if (r > 0)
        allIDs += ",";
      allIDs += displayDt->Rows[rowIndices[r]]["_RawID"]->ToString();
    }

    // === Header bar with radio button ===
    Panel ^ header = gcnew Panel();
    header->Dock = DockStyle::Top;
    header->Height = 42;
    header->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);

    RadioButton ^ rbCard = gcnew RadioButton();
    rbCard->Text = L"";
    rbCard->Tag = allIDs;
    rbCard->AccessibleName = firstStatus;
    rbCard->AccessibleDescription = firstCourier;
    rbCard->Location = System::Drawing::Point(8, 12);
    rbCard->Size = System::Drawing::Size(18, 18);
    rbCard->CheckedChanged += gcnew System::EventHandler(
        this, &adminForm::TransactionRadioButton_CheckedChanged);
    header->Controls->Add(rbCard);

    Label ^ lblCustName = gcnew Label();
    lblCustName->Text =
        L"Pembeli: " + customer + L" (" + itemCount + L" transaksi)";
    lblCustName->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold);
    lblCustName->ForeColor = System::Drawing::Color::White;
    lblCustName->Location = System::Drawing::Point(30, 2);
    lblCustName->AutoSize = true;
    header->Controls->Add(lblCustName);

    Label ^ lblHeaderStatus = gcnew Label();
    lblHeaderStatus->Text = L"Status: " + firstStatus;
    lblHeaderStatus->Font = gcnew System::Drawing::Font(L"Segoe UI", 8);
    lblHeaderStatus->ForeColor =
        System::Drawing::Color::FromArgb(200, 230, 201);
    lblHeaderStatus->Location = System::Drawing::Point(30, 24);
    lblHeaderStatus->AutoSize = true;
    header->Controls->Add(lblHeaderStatus);

    card->Controls->Add(header);
    yPos = 48;

    // === Item rows (26px each) ===
    for (int r = 0; r < rowIndices->Count; r++) {
      int idx = rowIndices[r];
      String ^ transId = displayDt->Rows[idx]["ID"]->ToString();
      String ^ date = displayDt->Rows[idx]["Date"]->ToString();
      String ^ status = displayDt->Rows[idx]["Status"]->ToString();

      Panel ^ itemRow = gcnew Panel();
      itemRow->Location = System::Drawing::Point(0, yPos);
      itemRow->Size = System::Drawing::Size(cardWidth - 2, 26);
      if (r % 2 == 1)
        itemRow->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);

      Label ^ lblTx = gcnew Label();
      lblTx->Text = L"  \x2022 " + transId + L" [" + date + L"]";
      lblTx->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblTx->Location = System::Drawing::Point(8, 4);
      lblTx->AutoSize = true;
      itemRow->Controls->Add(lblTx);

      Label ^ lblStatus = gcnew Label();
      lblStatus->Text = status;
      lblStatus->Font = gcnew System::Drawing::Font(
          L"Segoe UI", 9, System::Drawing::FontStyle::Bold);
      if (status == "pending")
        lblStatus->ForeColor = System::Drawing::Color::Orange;
      else if (status == "delivered" || status == "received")
        lblStatus->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
      else if (status == "cancelled")
        lblStatus->ForeColor = System::Drawing::Color::Red;
      else
        lblStatus->ForeColor = System::Drawing::Color::Gray;
      lblStatus->Location = System::Drawing::Point(cardWidth - 150, 4);
      lblStatus->AutoSize = true;
      itemRow->Controls->Add(lblStatus);

      card->Controls->Add(itemRow);
      yPos += 26;
    }

    // === Footer ===
    Panel ^ footer = gcnew Panel();
    footer->Location = System::Drawing::Point(0, yPos);
    footer->Size = System::Drawing::Size(cardWidth - 2, 40);
    footer->BackColor = System::Drawing::Color::FromArgb(245, 245, 245);

    Label ^ lblTotal = gcnew Label();
    lblTotal->Text = L"Total: " + itemCount + L" transaksi";
    lblTotal->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
    lblTotal->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
    lblTotal->Location = System::Drawing::Point(10, 10);
    lblTotal->AutoSize = true;
    footer->Controls->Add(lblTotal);

    card->Controls->Add(footer);
    yPos += 40;

    card->Height = yPos;
    flpTransactions->Controls->Add(card);
  }
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

    // If Courier, require courier type selection
    bool success = false;
    if (role == "Courier") {
      if (cmbCourierType->SelectedIndex < 0) {
        MessageBox::Show("Pilih tipe kurir (Reguler/Express)!", "Peringatan",
                         MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
      }
      String ^ courierType =
          (cmbCourierType->SelectedIndex == 1) ? "express" : "regular";
      success =
          DatabaseManager::RegisterUser(username, password, role, courierType);
    } else {
      success = DatabaseManager::RegisterUser(username, password, role);
    }

    if (success) {
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
  cmbCourierType->SelectedIndex = -1;
  lblCourierType->Visible = false;
  cmbCourierType->Visible = false;
}

System::Void adminForm::cmbNewRole_SelectedIndexChanged(System::Object ^ sender,
                                                        System::EventArgs ^ e) {
  bool isCourier = (cmbNewRole->SelectedIndex >= 0 &&
                    cmbNewRole->SelectedItem->ToString() == "Courier");
  lblCourierType->Visible = isCourier;
  cmbCourierType->Visible = isCourier;
  if (!isCourier) {
    cmbCourierType->SelectedIndex = -1;
  }
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

void adminForm::LoadFrequentProducts() {
  DataTable ^ dt = DatabaseManager::GetFrequentlyBoughtProducts();
  dgvFrequentProducts->DataSource = dt;
}

System::Void adminForm::btnRefreshFrequentProducts_Click(
    System::Object ^ sender, System::EventArgs ^ e) {
  LoadFrequentProducts();
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
  RadioButton ^ selectedRb = nullptr;

  // Find selected radio button
  for each (Control ^ card in flpTransactions->Controls) {
    if (card->GetType() == Panel::typeid) {
      for each (Control ^ ctrl in card->Controls) {
        if (ctrl->GetType() == RadioButton::typeid) {
          RadioButton ^ rb = safe_cast<RadioButton ^>(ctrl);
          if (rb->Checked) {
            selectedRb = rb;
            break;
          }
        }
      }
    }
  }

  if (selectedRb == nullptr) {
    MessageBox::Show("Pilih transaksi yang akan diubah statusnya! (Klik radio "
                     "button 'Pilih')",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  int transID = Convert::ToInt32(selectedRb->Tag);
  String ^ currentStatus = selectedRb->AccessibleName;

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
  RadioButton ^ selectedRb = nullptr;

  // Find selected radio button
  for each (Control ^ card in flpTransactions->Controls) {
    if (card->GetType() == Panel::typeid) {
      for each (Control ^ ctrl in card->Controls) {
        if (ctrl->GetType() == RadioButton::typeid) {
          RadioButton ^ rb = safe_cast<RadioButton ^>(ctrl);
          if (rb->Checked) {
            selectedRb = rb;
            break;
          }
        }
      }
    }
  }

  if (selectedRb == nullptr) {
    MessageBox::Show(
        "Pilih transaksi yang akan dihapus! (Klik radio button 'Pilih')",
        "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transID = Convert::ToInt32(selectedRb->Tag);

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
      LoadIncome();
    } else {
      MessageBox::Show("Gagal melakukan penarikan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

// Product Deactivation
System::Void adminForm::btnDeactivateProduct_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan dinonaktifkan!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  String ^ status =
      dgvProducts->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status == "Nonaktif") {
    MessageBox::Show("Produk sudah nonaktif!", "Info", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    return;
  }

  // Dialog for reason
  Form ^ dialog = gcnew Form();
  dialog->Text = L"Nonaktifkan Produk";
  dialog->Size = System::Drawing::Size(400, 220);
  dialog->StartPosition = FormStartPosition::CenterParent;
  dialog->FormBorderStyle =
      System::Windows::Forms::FormBorderStyle::FixedDialog;
  dialog->MaximizeBox = false;
  dialog->MinimizeBox = false;

  Label ^ lblInfo = gcnew Label();
  lblInfo->Text = L"Nonaktifkan produk: " + productName + L"\nMasukkan alasan:";
  lblInfo->Location = System::Drawing::Point(15, 15);
  lblInfo->Size = System::Drawing::Size(350, 35);
  dialog->Controls->Add(lblInfo);

  TextBox ^ txtReason = gcnew TextBox();
  txtReason->Multiline = true;
  txtReason->Location = System::Drawing::Point(15, 55);
  txtReason->Size = System::Drawing::Size(350, 60);
  dialog->Controls->Add(txtReason);

  Button ^ btnOK = gcnew Button();
  btnOK->Text = L"Nonaktifkan";
  btnOK->BackColor = System::Drawing::Color::FromArgb(211, 47, 47);
  btnOK->ForeColor = System::Drawing::Color::White;
  btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
  btnOK->Location = System::Drawing::Point(15, 130);
  btnOK->Size = System::Drawing::Size(120, 30);
  dialog->Controls->Add(btnOK);

  Button ^ btnCancel = gcnew Button();
  btnCancel->Text = L"Batal";
  btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  btnCancel->Location = System::Drawing::Point(150, 130);
  btnCancel->Size = System::Drawing::Size(100, 30);
  dialog->Controls->Add(btnCancel);

  dialog->AcceptButton = btnOK;
  dialog->CancelButton = btnCancel;

  if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
    String ^ reason = txtReason->Text->Trim();
    if (String::IsNullOrEmpty(reason))
      reason = L"Tidak ada keterangan";

    if (DatabaseManager::DeactivateProduct(productID, reason)) {
      MessageBox::Show("Produk '" + productName +
                           "' berhasil dinonaktifkan!\nNotifikasi telah "
                           "dikirim ke merchant.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadProducts();
    } else {
      MessageBox::Show("Gagal menonaktifkan produk!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void adminForm::btnActivateProduct_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan diaktifkan!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  String ^ status =
      dgvProducts->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status == "Aktif") {
    MessageBox::Show("Produk sudah aktif!", "Info", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    return;
  }

  if (DatabaseManager::ActivateProduct(productID)) {
    MessageBox::Show(
        "Produk '" + productName + "' berhasil diaktifkan kembali!", "Sukses",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
    LoadProducts();
  } else {
    MessageBox::Show("Gagal mengaktifkan produk!", "Error",
                     MessageBoxButtons::OK, MessageBoxIcon::Error);
  }
}

// Refund transaction
System::Void adminForm::btnRefundTransaction_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  RadioButton ^ selectedRb = nullptr;

  // Find selected radio button
  for each (Control ^ card in flpTransactions->Controls) {
    if (card->GetType() == Panel::typeid) {
      for each (Control ^ ctrl in card->Controls) {
        if (ctrl->GetType() == RadioButton::typeid) {
          RadioButton ^ rb = safe_cast<RadioButton ^>(ctrl);
          if (rb->Checked) {
            selectedRb = rb;
            break;
          }
        }
      }
    }
  }

  if (selectedRb == nullptr) {
    MessageBox::Show(
        "Pilih transaksi yang akan di-refund! (Klik radio button 'Pilih')",
        "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transID = Convert::ToInt32(selectedRb->Tag);
  String ^ currentStatus = selectedRb->AccessibleName;

  if (currentStatus != "shipping" && currentStatus != "delivered" &&
      currentStatus != "refund_requested") {
    MessageBox::Show(
        "Refund hanya bisa dilakukan untuk transaksi dengan status:\n"
        "'shipping', 'delivered', atau 'refund_requested'.\n\n"
        "Status saat ini: " +
            currentStatus,
        "Tidak Bisa Refund", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Refund transaksi ID: " + transID +
                           "?\n\nSaldo customer akan dikembalikan.\n"
                           "Pendapatan merchant & kurir akan ditarik kembali.",
                       "Konfirmasi Refund", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::RefundOrder(transID)) {
      MessageBox::Show(
          "Refund berhasil!\n\nSaldo customer telah dikembalikan.\n"
          "Notifikasi telah dikirim ke merchant.",
          "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadTransactions();
      LoadDashboardStats();
    } else {
      MessageBox::Show("Gagal melakukan refund!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

} // namespace ECommerce
