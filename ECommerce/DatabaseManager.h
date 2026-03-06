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
  static bool RegisterUser(String ^ username, String ^ password, String ^ role,
                           String ^ courierType);
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo,
                           int % outIsActive);
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo);

  // Helper: Format user ID based on role
  static String ^ FormatUserID(int id, String ^ role);

  // Admin functions - User management
  static DataTable ^ GetAllUsersTable();
  static bool SetUserActive(int userID, bool isActive);
  static bool DeleteUser(int userID);
  static bool UpdateUser(int userID, String ^ newUsername,
                         String ^ newPassword);
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
                         int merchantID, String ^ kategori, String ^ deskripsi);
  static bool UpdateProduct(int productID, String ^ nama, int harga, int komisi,
                            int stok, String ^ kategori, String ^ deskripsi);
  static bool DeleteProduct(int productID);
  static DataTable ^ GetTransactionsByMerchant(int merchantID);
  static array<int> ^ GetMerchantStats(int merchantID);
  static DataTable ^ GetAllProductsTable();
  static DataTable ^ GetAllProductsWithMerchantName();
  static DataTable ^ GetFrequentlyBoughtProducts();

  // ============ Customer Functions ============
  static int GetUserSaldo(int userID);
  static bool UpdateUserSaldo(int userID, int newSaldo);
  static bool TopUpSaldo(int userID, int amount);
  static bool PurchaseProduct(int productID, int customerID, bool chargeOngkir);
  static bool PurchaseProduct(int productID, int customerID, bool chargeOngkir,
                              String ^ shippingType, int courierID);
  static DataTable ^ GetExpressCouriers();
  static DataTable ^ GetTransactionsByCustomer(int customerID);
  static bool ConfirmDelivery(int transactionID, int customerID);
  static bool WithdrawSaldo(int userID, int amount);
  static bool CancelOrder(int transactionID, int customerID);

  // ============ Courier Functions ============
  static String ^ GetUserCourierType(int userID);
  static DataTable ^ GetPendingDeliveries(int courierID, String ^ courierType);
  static DataTable ^ GetActiveDeliveries(int courierID);
  static DataTable ^ GetDeliveryHistory(int courierID);
  static bool ClaimDelivery(int transactionID, int courierID);
  static bool CompleteDelivery(int transactionID, int courierID);
  static array<int> ^ GetCourierStats(int courierID);

  // ============ Product Deactivation ============
  static bool DeactivateProduct(int productID, String ^ reason);
  static bool ActivateProduct(int productID);

  // ============ Notifications ============
  static DataTable ^ GetNotifications(int userID);
  static int GetUnreadNotificationCount(int userID);
  static bool MarkNotificationsRead(int userID);

  // ============ Refund ============
  static bool RefundOrder(int transactionID);
  static bool RequestRefund(int transactionID, int customerID);

  // ============ Reviews ============
  static bool AddReview(int transactionID, int customerID, int productID,
                        int rating, String ^ comment);
  static double GetAverageRating(int productID);
  static bool HasReviewed(int transactionID);

  // ============ Order Tracking ============
  static bool AddTrackingEvent(int transactionID, String ^ status,
                               String ^ description);
  static DataTable ^ GetOrderTracking(int transactionID);

  // Admin transaction management
  static bool DeleteTransaction(int transactionID);
};
