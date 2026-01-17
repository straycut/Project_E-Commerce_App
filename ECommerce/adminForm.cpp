// adminForm.cpp - Implementation of adminForm event handlers
#include "adminForm.h"

namespace ECommerce {

System::Void adminForm::adminForm_Load(System::Object ^ sender,
                                       System::EventArgs ^ e) {
  LoadDashboardStats();
  LoadUsers();
  LoadIncome();
  LoadTransactions();
}

void adminForm::LoadDashboardStats() {
  array<int> ^ stats = DatabaseManager::GetDashboardStats();
  lblTotalUsers->Text = L"Total Users: " + stats[0];
  lblTotalMerchants->Text = L"Merchants: " + stats[1];
  lblTotalCustomers->Text = L"Customers: " + stats[2];
  lblTotalCouriers->Text = L"Couriers: " + stats[3];
  lblTotalTransactions->Text = L"Total Transactions: " + stats[4];
  lblTotalIncome->Text =
      L"Total Income: Rp " + String::Format("{0:N0}", stats[5]);
  lblActiveUsers->Text = L"Active Users: " + stats[6];
  lblInactiveUsers->Text = L"Inactive Users: " + stats[7];
}

void adminForm::LoadUsers() {
  dgvUsers->DataSource = DatabaseManager::GetAllUsersTable();
}

void adminForm::LoadIncome() {
  DataTable ^ dt = DatabaseManager::GetAllIncomeTable();
  dgvIncome->DataSource = dt;

  // Calculate total
  int total = 0;
  for each (DataRow ^ row in dt->Rows) {
    total += Convert::ToInt32(row["Amount"]);
  }
  lblTotalIncomeValue->Text = L"Total: Rp " + String::Format("{0:N0}", total);
}

void adminForm::LoadTransactions() {
  dgvTransactions->DataSource = DatabaseManager::GetAllTransactionsTable();
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

  int userID = Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["ID"]->Value);
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

  int userID = Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["ID"]->Value);
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

  int userID = Convert::ToInt32(dgvUsers->SelectedRows[0]->Cells["ID"]->Value);
  String ^ username =
      dgvUsers->SelectedRows[0]->Cells["Username"]->Value->ToString();
  String ^ role = dgvUsers->SelectedRows[0]->Cells["Role"]->Value->ToString();

  if (role == "Admin") {
    MessageBox::Show("Cannot delete Admin account!", "Warning",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
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

} // namespace ECommerce
