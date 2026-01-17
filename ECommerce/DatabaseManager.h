#pragma once

// Managed wrapper class for Windows Forms - declared here for other forms to
// use
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;

public
ref class DatabaseManager {
public:
  // Database lifecycle
  static bool InitializeDatabase();
  static void CloseDatabase();

  // User authentication
  static bool RegisterUser(String ^ username, String ^ password, String ^ role);
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo,
                           int % outIsActive);
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo);

  // Admin functions - User management
  static DataTable ^ GetAllUsersTable();
  static bool SetUserActive(int userID, bool isActive);
  static bool DeleteUser(int userID);

  // Admin functions - Income
  static DataTable ^ GetAllIncomeTable();

  // Admin functions - Transactions
  static DataTable ^ GetAllTransactionsTable();

  // Admin functions - Dashboard
  static array<int> ^ GetDashboardStats();
};
