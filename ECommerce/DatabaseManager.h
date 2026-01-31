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
  static String ^ GetUserAddress(int userID);
  static bool UpdateUserAddress(int userID, String ^ alamat);

  // Admin functions - Income
  static DataTable ^ GetAllIncomeTable();

  // Admin functions - Transactions
  static DataTable ^ GetAllTransactionsTable();
  static bool UpdateTransactionStatus(int transactionID, String ^ newStatus);

  // Admin functions - Dashboard
  static array<int> ^ GetDashboardStats();
  static array<int> ^ GetIncomeBreakdown();

  // ============ Merchant Functions ============
  static DataTable ^ GetProductsByMerchant(int merchantID);
  static bool AddProduct(String ^ nama, int harga, int komisi, int stok,
                         int merchantID);
  static bool UpdateProduct(int productID, String ^ nama, int harga, int komisi,
                            int stok);
  static bool DeleteProduct(int productID);
  static DataTable ^ GetTransactionsByMerchant(int merchantID);
  static array<int> ^ GetMerchantStats(int merchantID);
  static DataTable ^ GetAllProductsTable();
  static DataTable ^ GetAllProductsWithMerchantName();

  // ============ Customer Functions ============
  static int GetUserSaldo(int userID);
  static bool UpdateUserSaldo(int userID, int newSaldo);
  static bool TopUpSaldo(int userID, int amount);
  static bool PurchaseProduct(int productID, int customerID);
  static DataTable ^ GetTransactionsByCustomer(int customerID);
  static bool ConfirmDelivery(int transactionID, int customerID);
  static bool WithdrawSaldo(int userID, int amount);
  static bool CancelOrder(int transactionID, int customerID);

  // ============ Courier Functions ============
  static DataTable ^ GetPendingDeliveries();
  static DataTable ^ GetActiveDeliveries(int courierID);
  static DataTable ^ GetDeliveryHistory(int courierID);
  static bool ClaimDelivery(int transactionID, int courierID);
  static bool CompleteDelivery(int transactionID, int courierID);
  static array<int> ^ GetCourierStats(int courierID);

  // Admin transaction management
  static bool DeleteTransaction(int transactionID);
};
