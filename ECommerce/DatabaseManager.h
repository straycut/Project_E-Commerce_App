#pragma once

// Managed wrapper class for Windows Forms - declared here for other forms to
// use
using namespace System;
using namespace System::Windows::Forms;

public
ref class DatabaseManager {
public:
  static bool InitializeDatabase();
  static bool RegisterUser(String ^ username, String ^ password, String ^ role);
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo);
  static void CloseDatabase();
};
