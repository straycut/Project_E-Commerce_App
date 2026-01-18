// DatabaseManager.cpp - SQLite Database Operations
// This file mixes native C++ (SQLite) with managed C++/CLI code

// Native code section - compile without CLR
#pragma managed(push, off)

#include "sqlite3.h"
#include <string>
#include <vector>

// Forward declarations
struct sqlite3;
struct sqlite3_stmt;

struct UserData {
  int id;
  std::string username;
  std::string password;
  std::string role;
  int saldo;
  int isActive; // 1 = active, 0 = inactive
  std::string alamat; // address
};

struct ProductData {
  int id;
  std::string nama;
  int harga;
  int komisi;
  int merchantID;
};

struct TransactionData {
  int transID;
  int productID;
  int customerID;
  int affiliateID;
  std::string status;
  std::string createdAt;
  std::string customerAddress;
  std::string merchantAddress;
};

struct IncomeData {
  int id;
  int userID;
  std::string username;
  int transactionID;
  int amount;
  std::string type;
  std::string description;
  std::string createdAt;
};

struct DashboardStats {
  int totalUsers;
  int totalMerchants;
  int totalCustomers;
  int totalCouriers;
  int totalTransactions;
  int totalIncome;
  int activeUsers;
  int inactiveUsers;
};

struct IncomeBreakdown {
  int totalIncome;
  int appIncome;      // Income from commissions (application)
  int merchantIncome; // Income from sales (merchants)
  int courierIncome;  // Income from deliveries (couriers)
};

// Static member initialization
static sqlite3 *g_db = nullptr;
static const char *g_dbPath = "ecommerce.db";

// Native helper functions
static bool ExecuteSQL(const char *sql) {
  char *errMsg = nullptr;
  int rc = sqlite3_exec(g_db, sql, nullptr, nullptr, &errMsg);

  if (rc != SQLITE_OK) {
    if (errMsg) {
      sqlite3_free(errMsg);
    }
    return false;
  }
  return true;
}

static bool NativeInitialize() {
  if (g_db != nullptr) {
    return true;
  }

  int rc = sqlite3_open(g_dbPath, &g_db);
  if (rc != SQLITE_OK) {
    return false;
  }

  // Create Users table with is_active and alamat fields
  const char *createUsersSQL = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "username TEXT UNIQUE NOT NULL,"
                               "password TEXT NOT NULL,"
                               "role TEXT NOT NULL CHECK(role IN ('Admin', "
                               "'Merchant', 'Customer', 'Courier')),"
                               "saldo INTEGER DEFAULT 0,"
                               "is_active INTEGER DEFAULT 1,"
                               "alamat TEXT DEFAULT '',"
                               "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                               ");";

  if (!ExecuteSQL(createUsersSQL))
    return false;

  // Add columns if not exists (for existing databases)
  ExecuteSQL("ALTER TABLE users ADD COLUMN is_active INTEGER DEFAULT 1;");
  ExecuteSQL("ALTER TABLE users ADD COLUMN alamat TEXT DEFAULT '';");

  // Create Products table
  const char *createProductsSQL =
      "CREATE TABLE IF NOT EXISTS products ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "nama TEXT NOT NULL,"
      "harga INTEGER NOT NULL,"
      "komisi INTEGER NOT NULL,"
      "merchant_id INTEGER,"
      "FOREIGN KEY (merchant_id) REFERENCES users(id)"
      ");";

  if (!ExecuteSQL(createProductsSQL))
    return false;

  // Create Transactions table
  const char *createTransactionsSQL =
      "CREATE TABLE IF NOT EXISTS transactions ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "product_id INTEGER,"
      "customer_id INTEGER,"
      "affiliate_id INTEGER,"
      "status TEXT DEFAULT 'pending',"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (product_id) REFERENCES products(id),"
      "FOREIGN KEY (customer_id) REFERENCES users(id),"
      "FOREIGN KEY (affiliate_id) REFERENCES users(id)"
      ");";

  if (!ExecuteSQL(createTransactionsSQL))
    return false;

  // Create Income table
  const char *createIncomeSQL =
      "CREATE TABLE IF NOT EXISTS income ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "user_id INTEGER NOT NULL,"
      "transaction_id INTEGER,"
      "amount INTEGER NOT NULL,"
      "type TEXT NOT NULL CHECK(type IN ('commission', 'sale', 'delivery')),"
      "description TEXT,"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (user_id) REFERENCES users(id),"
      "FOREIGN KEY (transaction_id) REFERENCES transactions(id)"
      ");";

  if (!ExecuteSQL(createIncomeSQL))
    return false;

  // Insert default admin
  const char *insertAdminSQL = "INSERT OR IGNORE INTO users (username, "
                               "password, role, saldo, is_active) "
                               "VALUES ('admin', 'admin123', 'Admin', 0, 1);";

  ExecuteSQL(insertAdminSQL);

  return true;
}

static void NativeClose() {
  if (g_db != nullptr) {
    sqlite3_close(g_db);
    g_db = nullptr;
  }
}

static bool NativeRegisterUser(const std::string &username,
                               const std::string &password,
                               const std::string &role) {
  if (g_db == nullptr)
    return false;

  const char *sql = "INSERT INTO users (username, password, role, saldo, "
                    "is_active) VALUES (?, ?, ?, 0, 1);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

static UserData *NativeValidateUser(const std::string &username,
                                    const std::string &password) {
  if (g_db == nullptr)
    return nullptr;

  const char *sql =
      "SELECT id, username, password, role, saldo, COALESCE(is_active, 1) FROM "
      "users WHERE username = ? AND password = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return nullptr;

  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    UserData *user = new UserData();
    user->id = sqlite3_column_int(stmt, 0);
    user->username =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    user->password =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    user->role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    user->saldo = sqlite3_column_int(stmt, 4);
    user->isActive = sqlite3_column_int(stmt, 5);

    sqlite3_finalize(stmt);
    return user;
  }

  sqlite3_finalize(stmt);
  return nullptr;
}

// Get all users for admin
static std::vector<UserData> NativeGetAllUsers() {
  std::vector<UserData> users;
  if (g_db == nullptr)
    return users;

  const char *sql = "SELECT id, username, password, role, saldo, "
                    "COALESCE(is_active, 1), COALESCE(alamat, '') FROM users ORDER BY id;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return users;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    UserData user;
    user.id = sqlite3_column_int(stmt, 0);
    user.username =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    user.password =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    user.role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    user.saldo = sqlite3_column_int(stmt, 4);
    user.isActive = sqlite3_column_int(stmt, 5);
    const char *addr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    user.alamat = addr ? addr : "";
    users.push_back(user);
  }

  sqlite3_finalize(stmt);
  return users;
}

// Toggle user active status
static bool NativeSetUserActive(int userID, int isActive) {
  if (g_db == nullptr)
    return false;

  const char *sql = "UPDATE users SET is_active = ? WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, isActive);
  sqlite3_bind_int(stmt, 2, userID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Delete user
static bool NativeDeleteUser(int userID) {
  if (g_db == nullptr)
    return false;

  const char *sql = "DELETE FROM users WHERE id = ? AND role != 'Admin';";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, userID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Get all income with username
static std::vector<IncomeData> NativeGetAllIncome() {
  std::vector<IncomeData> incomes;
  if (g_db == nullptr)
    return incomes;

  const char *sql =
      "SELECT i.id, i.user_id, u.username, i.transaction_id, i.amount, i.type, "
      "COALESCE(i.description, ''), COALESCE(i.created_at, '') "
      "FROM income i LEFT JOIN users u ON i.user_id = u.id ORDER BY "
      "i.created_at DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return incomes;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    IncomeData income;
    income.id = sqlite3_column_int(stmt, 0);
    income.userID = sqlite3_column_int(stmt, 1);
    const char *uname =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    income.username = uname ? uname : "";
    income.transactionID = sqlite3_column_int(stmt, 3);
    income.amount = sqlite3_column_int(stmt, 4);
    income.type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    const char *desc =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    income.description = desc ? desc : "";
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    income.createdAt = created ? created : "";
    incomes.push_back(income);
  }

  sqlite3_finalize(stmt);
  return incomes;
}

// Get all transactions
static std::vector<TransactionData> NativeGetAllTransactions() {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  const char *sql = "SELECT id, product_id, customer_id, affiliate_id, status, "
                    "COALESCE(created_at, '') "
                    "FROM transactions ORDER BY id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3);
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Get dashboard statistics
static DashboardStats NativeGetDashboardStats() {
  DashboardStats stats = {0, 0, 0, 0, 0, 0, 0, 0};
  if (g_db == nullptr)
    return stats;

  sqlite3_stmt *stmt;

  // Count by role
  const char *sql1 = "SELECT role, COUNT(*) FROM users GROUP BY role;";
  if (sqlite3_prepare_v2(g_db, sql1, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *role =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      int count = sqlite3_column_int(stmt, 1);
      if (strcmp(role, "Admin") == 0)
        stats.totalUsers += count;
      else if (strcmp(role, "Merchant") == 0)
        stats.totalMerchants = count;
      else if (strcmp(role, "Customer") == 0)
        stats.totalCustomers = count;
      else if (strcmp(role, "Courier") == 0)
        stats.totalCouriers = count;
      stats.totalUsers += count;
    }
    sqlite3_finalize(stmt);
  }

  // Active/Inactive users
  const char *sql2 =
      "SELECT COALESCE(is_active, 1), COUNT(*) FROM users GROUP BY is_active;";
  if (sqlite3_prepare_v2(g_db, sql2, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      int isActive = sqlite3_column_int(stmt, 0);
      int count = sqlite3_column_int(stmt, 1);
      if (isActive == 1)
        stats.activeUsers = count;
      else
        stats.inactiveUsers = count;
    }
    sqlite3_finalize(stmt);
  }

  // Total transactions
  const char *sql3 = "SELECT COUNT(*) FROM transactions;";
  if (sqlite3_prepare_v2(g_db, sql3, -1, &stmt, nullptr) == SQLITE_OK) {
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalTransactions = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Total income
  const char *sql4 = "SELECT COALESCE(SUM(amount), 0) FROM income;";
  if (sqlite3_prepare_v2(g_db, sql4, -1, &stmt, nullptr) == SQLITE_OK) {
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalIncome = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  return stats;
}

// Get income breakdown by type
static IncomeBreakdown NativeGetIncomeBreakdown() {
  IncomeBreakdown breakdown = {0, 0, 0, 0};
  if (g_db == nullptr)
    return breakdown;

  sqlite3_stmt *stmt;

  // Get income by type
  const char *sql = "SELECT type, COALESCE(SUM(amount), 0) FROM income GROUP BY type;";
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      int amount = sqlite3_column_int(stmt, 1);
      if (type) {
        if (strcmp(type, "commission") == 0)
          breakdown.appIncome = amount;
        else if (strcmp(type, "sale") == 0)
          breakdown.merchantIncome = amount;
        else if (strcmp(type, "delivery") == 0)
          breakdown.courierIncome = amount;
      }
    }
    sqlite3_finalize(stmt);
  }

  breakdown.totalIncome = breakdown.appIncome + breakdown.merchantIncome + breakdown.courierIncome;
  return breakdown;
}

// ============ Merchant Functions ============

// Get products by merchant ID
static std::vector<ProductData> NativeGetProductsByMerchant(int merchantID) {
  std::vector<ProductData> products;
  if (g_db == nullptr)
    return products;

  const char *sql = "SELECT id, nama, harga, komisi, merchant_id FROM products "
                    "WHERE merchant_id = ? ORDER BY id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return products;

  sqlite3_bind_int(stmt, 1, merchantID);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    ProductData product;
    product.id = sqlite3_column_int(stmt, 0);
    const char *nama =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    product.nama = nama ? nama : "";
    product.harga = sqlite3_column_int(stmt, 2);
    product.komisi = sqlite3_column_int(stmt, 3);
    product.merchantID = sqlite3_column_int(stmt, 4);
    products.push_back(product);
  }

  sqlite3_finalize(stmt);
  return products;
}

// Add new product
static bool NativeAddProduct(const std::string &nama, int harga, int komisi,
                             int merchantID) {
  if (g_db == nullptr)
    return false;

  const char *sql = "INSERT INTO products (nama, harga, komisi, merchant_id) "
                    "VALUES (?, ?, ?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, nama.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, harga);
  sqlite3_bind_int(stmt, 3, komisi);
  sqlite3_bind_int(stmt, 4, merchantID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Update product
static bool NativeUpdateProduct(int productID, const std::string &nama,
                                int harga, int komisi) {
  if (g_db == nullptr)
    return false;

  const char *sql =
      "UPDATE products SET nama = ?, harga = ?, komisi = ? WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, nama.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, harga);
  sqlite3_bind_int(stmt, 3, komisi);
  sqlite3_bind_int(stmt, 4, productID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Delete product
static bool NativeDeleteProduct(int productID) {
  if (g_db == nullptr)
    return false;

  const char *sql = "DELETE FROM products WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, productID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Get transactions by merchant
static std::vector<TransactionData>
NativeGetTransactionsByMerchant(int merchantID) {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, COALESCE(t.courier_id, 0), "
      "t.status, COALESCE(t.created_at, '') "
      "FROM transactions t "
      "INNER JOIN products p ON t.product_id = p.id "
      "WHERE p.merchant_id = ? "
      "ORDER BY t.id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  sqlite3_bind_int(stmt, 1, merchantID);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3); // reusing as courierID
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Get merchant statistics
struct MerchantStats {
  int totalProducts;
  int totalSales;
  int totalIncome;
};

static MerchantStats NativeGetMerchantStats(int merchantID) {
  MerchantStats stats = {0, 0, 0};
  if (g_db == nullptr)
    return stats;

  sqlite3_stmt *stmt;

  // Total products
  const char *sql1 = "SELECT COUNT(*) FROM products WHERE merchant_id = ?;";
  if (sqlite3_prepare_v2(g_db, sql1, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalProducts = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Total sales (completed transactions)
  const char *sql2 = "SELECT COUNT(*) FROM transactions t "
                     "INNER JOIN products p ON t.product_id = p.id "
                     "WHERE p.merchant_id = ?;";
  if (sqlite3_prepare_v2(g_db, sql2, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalSales = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Total income
  const char *sql3 = "SELECT COALESCE(SUM(amount), 0) FROM income WHERE "
                     "user_id = ? AND type = 'sale';";
  if (sqlite3_prepare_v2(g_db, sql3, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalIncome = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  return stats;
}

// Get all products (for customer catalog)
static std::vector<ProductData> NativeGetAllProducts() {
  std::vector<ProductData> products;
  if (g_db == nullptr)
    return products;

  const char *sql = "SELECT id, nama, harga, komisi, merchant_id FROM products "
                    "ORDER BY id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return products;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    ProductData product;
    product.id = sqlite3_column_int(stmt, 0);
    const char *nama =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    product.nama = nama ? nama : "";
    product.harga = sqlite3_column_int(stmt, 2);
    product.komisi = sqlite3_column_int(stmt, 3);
    product.merchantID = sqlite3_column_int(stmt, 4);
    products.push_back(product);
  }

  sqlite3_finalize(stmt);
  return products;
}

// ============ Customer Functions ============

// Get user saldo
static int NativeGetUserSaldo(int userID) {
  if (g_db == nullptr)
    return 0;

  const char *sql = "SELECT saldo FROM users WHERE id = ?;";
  sqlite3_stmt *stmt;
  int saldo = 0;

  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, userID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      saldo = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  return saldo;
}

// Update user saldo
static bool NativeUpdateUserSaldo(int userID, int newSaldo) {
  if (g_db == nullptr)
    return false;

  const char *sql = "UPDATE users SET saldo = ? WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, newSaldo);
  sqlite3_bind_int(stmt, 2, userID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Get user address
static std::string NativeGetUserAddress(int userID) {
  if (g_db == nullptr)
    return "";

  const char *sql = "SELECT COALESCE(alamat, '') FROM users WHERE id = ?;";
  sqlite3_stmt *stmt;
  std::string alamat = "";

  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, userID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *addr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      alamat = addr ? addr : "";
    }
    sqlite3_finalize(stmt);
  }

  return alamat;
}

// Update user address
static bool NativeUpdateUserAddress(int userID, const std::string &alamat) {
  if (g_db == nullptr)
    return false;

  const char *sql = "UPDATE users SET alamat = ? WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, alamat.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, userID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Purchase product - create transaction and handle money
static bool NativePurchaseProduct(int productID, int customerID) {
  if (g_db == nullptr)
    return false;

  // Get product info
  const char *sqlProduct =
      "SELECT harga, komisi, merchant_id FROM products WHERE id = ?;";
  sqlite3_stmt *stmt;
  int harga = 0, komisi = 0, merchantID = 0;

  if (sqlite3_prepare_v2(g_db, sqlProduct, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      harga = sqlite3_column_int(stmt, 0);
      komisi = sqlite3_column_int(stmt, 1);
      merchantID = sqlite3_column_int(stmt, 2);
    }
    sqlite3_finalize(stmt);
  }

  if (harga == 0 || merchantID == 0)
    return false;

  // Check customer saldo
  int saldo = NativeGetUserSaldo(customerID);
  if (saldo < harga)
    return false;

  // Begin transaction
  ExecuteSQL("BEGIN TRANSACTION;");

  // Deduct customer saldo
  if (!NativeUpdateUserSaldo(customerID, saldo - harga)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Calculate merchant income (harga - komisi aplikasi)
  int merchantIncome = harga - (harga * komisi / 100);
  int merchantSaldo = NativeGetUserSaldo(merchantID);
  if (!NativeUpdateUserSaldo(merchantID, merchantSaldo + merchantIncome)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Create transaction
  const char *sqlTrans = "INSERT INTO transactions (product_id, customer_id, "
                         "status) VALUES (?, ?, 'pending');";
  if (sqlite3_prepare_v2(g_db, sqlTrans, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    sqlite3_bind_int(stmt, 2, customerID);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
      ExecuteSQL("ROLLBACK;");
      return false;
    }
  }

  int transID = (int)sqlite3_last_insert_rowid(g_db);

  // Add income record for merchant
  const char *sqlIncome =
      "INSERT INTO income (user_id, transaction_id, amount, type, description) "
      "VALUES (?, ?, ?, 'sale', 'Penjualan produk');";
  if (sqlite3_prepare_v2(g_db, sqlIncome, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    sqlite3_bind_int(stmt, 2, transID);
    sqlite3_bind_int(stmt, 3, merchantIncome);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  ExecuteSQL("COMMIT;");
  return true;
}

// Get transactions by customer
static std::vector<TransactionData>
NativeGetTransactionsByCustomer(int customerID) {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  const char *sql = "SELECT id, product_id, customer_id, COALESCE(courier_id, "
                    "0), status, COALESCE(created_at, '') "
                    "FROM transactions WHERE customer_id = ? ORDER BY id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  sqlite3_bind_int(stmt, 1, customerID);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3); // courierID
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// ============ Courier Functions ============

// Add courier_id column if not exists
static void EnsureCourierColumn() {
  ExecuteSQL("ALTER TABLE transactions ADD COLUMN courier_id INTEGER;");
}

// Get pending deliveries (no courier assigned)
static std::vector<TransactionData> NativeGetPendingDeliveries() {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  EnsureCourierColumn();

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, 0, t.status, "
      "COALESCE(t.created_at, ''), "
      "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, '') "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "WHERE t.status = 'pending' AND (t.courier_id IS NULL OR "
      "t.courier_id = 0) "
      "ORDER BY t.id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3);
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    
    const char *custAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    
    const char *merchAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Get active deliveries (courier assigned, status = shipping)
static std::vector<TransactionData> NativeGetActiveDeliveries(int courierID) {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, t.courier_id, t.status, "
      "COALESCE(t.created_at, ''), "
      "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, '') "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "WHERE t.courier_id = ? AND t.status = 'shipping' "
      "ORDER BY t.id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  sqlite3_bind_int(stmt, 1, courierID);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3);
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    
    const char *custAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    
    const char *merchAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Get delivery history (completed by courier)
static std::vector<TransactionData> NativeGetDeliveryHistory(int courierID) {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, t.courier_id, t.status, "
      "COALESCE(t.created_at, ''), "
      "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, '') "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "WHERE t.courier_id = ? AND t.status = 'delivered' "
      "ORDER BY t.id DESC;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return transactions;

  sqlite3_bind_int(stmt, 1, courierID);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    TransactionData trans;
    trans.transID = sqlite3_column_int(stmt, 0);
    trans.productID = sqlite3_column_int(stmt, 1);
    trans.customerID = sqlite3_column_int(stmt, 2);
    trans.affiliateID = sqlite3_column_int(stmt, 3);
    trans.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    const char *created =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    trans.createdAt = created ? created : "";
    
    const char *custAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    
    const char *merchAddr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Claim delivery (courier takes the order)
static bool NativeClaimDelivery(int transactionID, int courierID) {
  if (g_db == nullptr)
    return false;

  const char *sql =
      "UPDATE transactions SET courier_id = ?, status = 'shipping' "
      "WHERE id = ? AND (courier_id IS NULL OR courier_id = 0);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, courierID);
  sqlite3_bind_int(stmt, 2, transactionID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE && sqlite3_changes(g_db) > 0;
}

// Complete delivery
static bool NativeCompleteDelivery(int transactionID, int courierID) {
  if (g_db == nullptr)
    return false;

  // Update transaction status
  const char *sqlUpdate = "UPDATE transactions SET status = 'delivered' WHERE "
                          "id = ? AND courier_id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sqlUpdate, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_int(stmt, 2, courierID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE || sqlite3_changes(g_db) == 0)
    return false;

  // Add income for courier (fixed delivery fee: 10000)
  int deliveryFee = 10000;
  int courierSaldo = NativeGetUserSaldo(courierID);
  NativeUpdateUserSaldo(courierID, courierSaldo + deliveryFee);

  const char *sqlIncome =
      "INSERT INTO income (user_id, transaction_id, amount, type, description) "
      "VALUES (?, ?, ?, 'delivery', 'Ongkos kirim');";
  if (sqlite3_prepare_v2(g_db, sqlIncome, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, courierID);
    sqlite3_bind_int(stmt, 2, transactionID);
    sqlite3_bind_int(stmt, 3, deliveryFee);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  return true;
}

// Get courier statistics
struct CourierStats {
  int todayDeliveries;
  int totalDeliveries;
  int totalIncome;
};

static CourierStats NativeGetCourierStats(int courierID) {
  CourierStats stats = {0, 0, 0};
  if (g_db == nullptr)
    return stats;

  sqlite3_stmt *stmt;

  // Today's deliveries
  const char *sql1 = "SELECT COUNT(*) FROM transactions WHERE courier_id = ? "
                     "AND status = 'delivered' "
                     "AND DATE(created_at) = DATE('now');";
  if (sqlite3_prepare_v2(g_db, sql1, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, courierID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.todayDeliveries = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Total deliveries
  const char *sql2 = "SELECT COUNT(*) FROM transactions WHERE courier_id = ? "
                     "AND status = 'delivered';";
  if (sqlite3_prepare_v2(g_db, sql2, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, courierID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalDeliveries = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Total income from deliveries
  const char *sql3 = "SELECT COALESCE(SUM(amount), 0) FROM income WHERE "
                     "user_id = ? AND type = 'delivery';";
  if (sqlite3_prepare_v2(g_db, sql3, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, courierID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalIncome = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  return stats;
}

#pragma managed(pop)

// ============ Managed Wrapper Implementation ============

#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Collections::Generic;

public
ref class DatabaseManager {
public:
  static bool InitializeDatabase() { return NativeInitialize(); }

  static void CloseDatabase() { NativeClose(); }

  static bool RegisterUser(String ^ username, String ^ password,
                           String ^ role) {
    std::string user = msclr::interop::marshal_as<std::string>(username);
    std::string pass = msclr::interop::marshal_as<std::string>(password);
    std::string r = msclr::interop::marshal_as<std::string>(role);

    return NativeRegisterUser(user, pass, r);
  }

  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID, int % outSaldo,
                           int % outIsActive) {
    std::string user = msclr::interop::marshal_as<std::string>(username);
    std::string pass = msclr::interop::marshal_as<std::string>(password);

    UserData *userData = NativeValidateUser(user, pass);

    if (userData != nullptr) {
      outUserID = userData->id;
      outRole = gcnew String(userData->role.c_str());
      outSaldo = userData->saldo;
      outIsActive = userData->isActive;
      delete userData;
      return true;
    }

    return false;
  }

  // Overload for backward compatibility
  static bool ValidateUser(String ^ username, String ^ password,
                           String ^ % outRole, int % outUserID,
                           int % outSaldo) {
    int isActive;
    return ValidateUser(username, password, outRole, outUserID, outSaldo,
                        isActive);
  }

  // Get all users as DataTable for DataGridView
  static DataTable ^ GetAllUsersTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("Username", String::typeid);
    dt->Columns->Add("Role", String::typeid);
    dt->Columns->Add("Saldo", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Alamat", String::typeid);

    std::vector<UserData> users = NativeGetAllUsers();
    for (const auto &user : users) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = user.id;
      row["Username"] = gcnew String(user.username.c_str());
      row["Role"] = gcnew String(user.role.c_str());
      row["Saldo"] = user.saldo;
      row["Status"] = user.isActive ? "Active" : "Inactive";
      row["Alamat"] = gcnew String(user.alamat.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Set user active/inactive
  static bool SetUserActive(int userID, bool isActive) {
    return NativeSetUserActive(userID, isActive ? 1 : 0);
  }

  // Delete user
  static bool DeleteUser(int userID) { return NativeDeleteUser(userID); }

  // Get user address
  static String ^ GetUserAddress(int userID) {
    std::string addr = NativeGetUserAddress(userID);
    return gcnew String(addr.c_str());
  }

  // Update user address
  static bool UpdateUserAddress(int userID, String ^ alamat) {
    std::string addrNative = msclr::interop::marshal_as<std::string>(alamat);
    return NativeUpdateUserAddress(userID, addrNative);
  }

  // Get all income as DataTable
  static DataTable ^ GetAllIncomeTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("Username", String::typeid);
    dt->Columns->Add("Amount", Int32::typeid);
    dt->Columns->Add("Type", String::typeid);
    dt->Columns->Add("Description", String::typeid);
    dt->Columns->Add("Date", String::typeid);

    std::vector<IncomeData> incomes = NativeGetAllIncome();
    for (const auto &income : incomes) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = income.id;
      row["Username"] = gcnew String(income.username.c_str());
      row["Amount"] = income.amount;
      row["Type"] = gcnew String(income.type.c_str());
      row["Description"] = gcnew String(income.description.c_str());
      row["Date"] = gcnew String(income.createdAt.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get all transactions as DataTable
  static DataTable ^ GetAllTransactionsTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("CourierID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);

    std::vector<TransactionData> transactions = NativeGetAllTransactions();
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["CourierID"] = trans.affiliateID;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get dashboard statistics
  static array<int> ^
      GetDashboardStats() {
        DashboardStats stats = NativeGetDashboardStats();
        array<int> ^ result = gcnew array<int>(8);
        result[0] = stats.totalUsers;
        result[1] = stats.totalMerchants;
        result[2] = stats.totalCustomers;
        result[3] = stats.totalCouriers;
        result[4] = stats.totalTransactions;
        result[5] = stats.totalIncome;
        result[6] = stats.activeUsers;
        result[7] = stats.inactiveUsers;
        return result;
      }

      // Get income breakdown: [0]=total, [1]=app, [2]=merchant, [3]=courier
      static array<int> ^
          GetIncomeBreakdown() {
            IncomeBreakdown breakdown = NativeGetIncomeBreakdown();
            array<int> ^ result = gcnew array<int>(4);
            result[0] = breakdown.totalIncome;
            result[1] = breakdown.appIncome;
            result[2] = breakdown.merchantIncome;
            result[3] = breakdown.courierIncome;
            return result;
          }

      // ============ Merchant Functions ============

      // Get products by merchant as DataTable
      static DataTable
      ^ GetProductsByMerchant(int merchantID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("Nama", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Komisi", Int32::typeid);

    std::vector<ProductData> products = NativeGetProductsByMerchant(merchantID);
    for (const auto &product : products) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = product.id;
      row["Nama"] = gcnew String(product.nama.c_str());
      row["Harga"] = product.harga;
      row["Komisi"] = product.komisi;
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Add new product
  static bool AddProduct(String ^ nama, int harga, int komisi, int merchantID) {
    std::string namaNative = msclr::interop::marshal_as<std::string>(nama);
    return NativeAddProduct(namaNative, harga, komisi, merchantID);
  }

  // Update product
  static bool UpdateProduct(int productID, String ^ nama, int harga,
                            int komisi) {
    std::string namaNative = msclr::interop::marshal_as<std::string>(nama);
    return NativeUpdateProduct(productID, namaNative, harga, komisi);
  }

  // Delete product
  static bool DeleteProduct(int productID) {
    return NativeDeleteProduct(productID);
  }

  // Get transactions by merchant as DataTable
  static DataTable ^ GetTransactionsByMerchant(int merchantID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("CourierID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetTransactionsByMerchant(merchantID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["CourierID"] = trans.affiliateID; // reused as courierID
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get merchant statistics: [0]=totalProducts, [1]=totalSales, [2]=totalIncome
  static array<int> ^
      GetMerchantStats(int merchantID) {
        MerchantStats stats = NativeGetMerchantStats(merchantID);
        array<int> ^ result = gcnew array<int>(3);
        result[0] = stats.totalProducts;
        result[1] = stats.totalSales;
        result[2] = stats.totalIncome;
        return result;
      }

      // Get all products as DataTable (for customer catalog)
      static DataTable
      ^ GetAllProductsTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("Nama", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Komisi", Int32::typeid);
    dt->Columns->Add("MerchantID", Int32::typeid);

    std::vector<ProductData> products = NativeGetAllProducts();
    for (const auto &product : products) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = product.id;
      row["Nama"] = gcnew String(product.nama.c_str());
      row["Harga"] = product.harga;
      row["Komisi"] = product.komisi;
      row["MerchantID"] = product.merchantID;
      dt->Rows->Add(row);
    }

    return dt;
  }

  // ============ Customer Functions ============

  // Get user saldo
  static int GetUserSaldo(int userID) { return NativeGetUserSaldo(userID); }

  // Update user saldo (for top up)
  static bool UpdateUserSaldo(int userID, int newSaldo) {
    return NativeUpdateUserSaldo(userID, newSaldo);
  }

  // Top up saldo
  static bool TopUpSaldo(int userID, int amount) {
    int currentSaldo = NativeGetUserSaldo(userID);
    return NativeUpdateUserSaldo(userID, currentSaldo + amount);
  }

  // Purchase product
  static bool PurchaseProduct(int productID, int customerID) {
    return NativePurchaseProduct(productID, customerID);
  }

  // Get transactions by customer as DataTable
  static DataTable ^ GetTransactionsByCustomer(int customerID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("CourierID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetTransactionsByCustomer(customerID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["CourierID"] = trans.affiliateID;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // ============ Courier Functions ============

  // Get pending deliveries as DataTable
  static DataTable ^ GetPendingDeliveries() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    std::vector<TransactionData> transactions = NativeGetPendingDeliveries();
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      row["Alamat Customer"] = gcnew String(trans.customerAddress.c_str());
      row["Alamat Merchant"] = gcnew String(trans.merchantAddress.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get active deliveries by courier as DataTable
  static DataTable ^ GetActiveDeliveries(int courierID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetActiveDeliveries(courierID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      row["Alamat Customer"] = gcnew String(trans.customerAddress.c_str());
      row["Alamat Merchant"] = gcnew String(trans.merchantAddress.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get delivery history by courier as DataTable
  static DataTable ^ GetDeliveryHistory(int courierID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetDeliveryHistory(courierID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      row["Alamat Customer"] = gcnew String(trans.customerAddress.c_str());
      row["Alamat Merchant"] = gcnew String(trans.merchantAddress.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Claim delivery
  static bool ClaimDelivery(int transactionID, int courierID) {
    return NativeClaimDelivery(transactionID, courierID);
  }

  // Complete delivery
  static bool CompleteDelivery(int transactionID, int courierID) {
    return NativeCompleteDelivery(transactionID, courierID);
  }

  // Get courier statistics: [0]=todayDeliveries, [1]=totalDeliveries,
  // [2]=totalIncome
  static array<int> ^ GetCourierStats(int courierID) {
    CourierStats stats = NativeGetCourierStats(courierID);
    array<int> ^ result = gcnew array<int>(3);
    result[0] = stats.todayDeliveries;
    result[1] = stats.totalDeliveries;
    result[2] = stats.totalIncome;
    return result;
  }
};
