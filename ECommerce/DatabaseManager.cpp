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
  int isActive;       // 1 = active, 0 = inactive
  std::string alamat; // address
};

struct ProductData {
  int id;
  std::string nama;
  std::string kategori;
  std::string deskripsi;
  int harga;
  int komisi;
  int stok;
  int merchantID;
  std::string merchantName;
  std::string merchantAlamat;
  int isActive;
};

struct TransactionData {
  int transID;
  int productID;
  int customerID;
  int affiliateID;
  int totalPrice;
  std::string status;
  std::string createdAt;
  std::string customerAddress;
  std::string merchantAddress;
  std::string customerName;
  std::string courierName;
  std::string productName;
  int productPrice;
  std::string shippingType;
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
  ExecuteSQL(
      "ALTER TABLE users ADD COLUMN courier_type TEXT DEFAULT 'regular';");

  // Create Products table with stok column
  const char *createProductsSQL =
      "CREATE TABLE IF NOT EXISTS products ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "nama TEXT NOT NULL,"
      "harga INTEGER NOT NULL,"
      "komisi INTEGER NOT NULL,"
      "stok INTEGER DEFAULT 0,"
      "merchant_id INTEGER,"
      "FOREIGN KEY (merchant_id) REFERENCES users(id)"
      ");";

  if (!ExecuteSQL(createProductsSQL))
    return false;

  // Add stok column if not exists (for existing databases)
  ExecuteSQL("ALTER TABLE products ADD COLUMN stok INTEGER DEFAULT 0;");

  // Add kategori and deskripsi columns if not exists
  ExecuteSQL("ALTER TABLE products ADD COLUMN kategori TEXT DEFAULT '';");
  ExecuteSQL("ALTER TABLE products ADD COLUMN deskripsi TEXT DEFAULT '';");

  // Update existing products with 0 commission to fixed 5% commission
  ExecuteSQL(
      "UPDATE products SET komisi = 5 WHERE komisi = 0 OR komisi IS NULL;");

  // Create Transactions table
  const char *createTransactionsSQL =
      "CREATE TABLE IF NOT EXISTS transactions ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "product_id INTEGER,"
      "customer_id INTEGER,"
      "affiliate_id INTEGER,"
      "status TEXT DEFAULT 'pending',"
      "shipping_type TEXT DEFAULT 'regular',"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (product_id) REFERENCES products(id),"
      "FOREIGN KEY (customer_id) REFERENCES users(id),"
      "FOREIGN KEY (affiliate_id) REFERENCES users(id)"
      ");";

  if (!ExecuteSQL(createTransactionsSQL))
    return false;

  // Add shipping_type column if not exists (for existing databases)
  ExecuteSQL("ALTER TABLE transactions ADD COLUMN shipping_type TEXT DEFAULT "
             "'regular';");

  // Update income type constraint for withdrawal support
  // Note: SQLite cannot ALTER CHECK constraints, but new rows will use the
  // updated CREATE TABLE. For existing databases, the INSERT will succeed
  // because SQLite does not enforce CHECK on ALTER.

  // Create Income table
  const char *createIncomeSQL =
      "CREATE TABLE IF NOT EXISTS income ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "user_id INTEGER NOT NULL,"
      "transaction_id INTEGER,"
      "amount INTEGER NOT NULL,"
      "type TEXT NOT NULL CHECK(type IN ('commission', 'sale', 'delivery', "
      "'withdrawal')),"
      "description TEXT,"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (user_id) REFERENCES users(id),"
      "FOREIGN KEY (transaction_id) REFERENCES transactions(id)"
      ");";

  if (!ExecuteSQL(createIncomeSQL))
    return false;

  // Add is_active column to products
  ExecuteSQL("ALTER TABLE products ADD COLUMN is_active INTEGER DEFAULT 1;");

  // Create Notifications table
  const char *createNotificationsSQL =
      "CREATE TABLE IF NOT EXISTS notifications ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "user_id INTEGER NOT NULL,"
      "message TEXT NOT NULL,"
      "reason TEXT,"
      "is_read INTEGER DEFAULT 0,"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (user_id) REFERENCES users(id)"
      ");";
  ExecuteSQL(createNotificationsSQL);

  // Create Reviews table
  const char *createReviewsSQL =
      "CREATE TABLE IF NOT EXISTS reviews ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "transaction_id INTEGER UNIQUE,"
      "customer_id INTEGER,"
      "product_id INTEGER,"
      "rating INTEGER CHECK(rating BETWEEN 1 AND 5),"
      "comment TEXT,"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (transaction_id) REFERENCES transactions(id),"
      "FOREIGN KEY (customer_id) REFERENCES users(id),"
      "FOREIGN KEY (product_id) REFERENCES products(id)"
      ");";
  ExecuteSQL(createReviewsSQL);

  // Create Order Tracking table
  const char *createTrackingSQL =
      "CREATE TABLE IF NOT EXISTS order_tracking ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "transaction_id INTEGER,"
      "status TEXT,"
      "description TEXT,"
      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (transaction_id) REFERENCES transactions(id)"
      ");";
  ExecuteSQL(createTrackingSQL);

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

// Register user with courier_type
static bool NativeRegisterUser(const std::string &username,
                               const std::string &password,
                               const std::string &role,
                               const std::string &courierType) {
  if (g_db == nullptr)
    return false;

  const char *sql =
      "INSERT INTO users (username, password, role, saldo, is_active, "
      "courier_type) VALUES (?, ?, ?, 0, 1, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, courierType.c_str(), -1, SQLITE_STATIC);

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

  const char *sql =
      "SELECT id, username, password, role, saldo, "
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
    const char *addr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
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

  const char *sql = "DELETE FROM users WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, userID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Update user (username and optionally password)
static bool NativeUpdateUser(int userID, const std::string &newUsername,
                             const std::string &newPassword) {
  if (g_db == nullptr)
    return false;

  sqlite3_stmt *stmt;
  int rc;

  if (newPassword.empty()) {
    // Update username only
    const char *sql = "UPDATE users SET username = ? WHERE id = ?;";
    rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
      return false;
    sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, userID);
  } else {
    // Update both username and password
    const char *sql =
        "UPDATE users SET username = ?, password = ? WHERE id = ?;";
    rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
      return false;
    sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, newPassword.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, userID);
  }

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

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, COALESCE(t.courier_id, 0), "
      "t.status, "
      "COALESCE(t.created_at, ''), "
      "COALESCE(u_cust.username, ''), COALESCE(u_courier.username, ''), "
      "COALESCE(u_merch.alamat, ''), COALESCE(u_cust.alamat, '') "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN users u_courier ON t.courier_id = u_courier.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
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
    const char *custName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerName = custName ? custName : "";
    const char *courierName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.courierName = courierName ? courierName : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    trans.customerAddress = custAddr ? custAddr : "";
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

  // Total users count
  const char *sqlTotal = "SELECT COUNT(*) FROM users;";
  if (sqlite3_prepare_v2(g_db, sqlTotal, -1, &stmt, nullptr) == SQLITE_OK) {
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      stats.totalUsers = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }

  // Count by role
  const char *sql1 = "SELECT role, COUNT(*) FROM users GROUP BY role;";
  if (sqlite3_prepare_v2(g_db, sql1, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *role =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      int count = sqlite3_column_int(stmt, 1);
      if (strcmp(role, "Merchant") == 0)
        stats.totalMerchants = count;
      else if (strcmp(role, "Customer") == 0)
        stats.totalCustomers = count;
      else if (strcmp(role, "Courier") == 0)
        stats.totalCouriers = count;
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
  const char *sql =
      "SELECT type, COALESCE(SUM(amount), 0) FROM income GROUP BY type;";
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *type =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
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

  breakdown.totalIncome =
      breakdown.appIncome + breakdown.merchantIncome + breakdown.courierIncome;
  return breakdown;
}

// ============ Merchant Functions ============

// Get products by merchant ID
static std::vector<ProductData> NativeGetProductsByMerchant(int merchantID) {
  std::vector<ProductData> products;
  if (g_db == nullptr)
    return products;

  const char *sql =
      "SELECT id, nama, harga, komisi, stok, merchant_id, "
      "COALESCE(kategori, ''), COALESCE(deskripsi, '') FROM products "
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
    product.stok = sqlite3_column_int(stmt, 4);
    product.merchantID = sqlite3_column_int(stmt, 5);
    const char *kat =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    product.kategori = kat ? kat : "";
    const char *desk =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    product.deskripsi = desk ? desk : "";
    products.push_back(product);
  }

  sqlite3_finalize(stmt);
  return products;
}

// Add new product
static bool NativeAddProduct(const std::string &nama, int harga, int komisi,
                             int stok, int merchantID,
                             const std::string &kategori,
                             const std::string &deskripsi) {
  if (g_db == nullptr)
    return false;

  const char *sql = "INSERT INTO products (nama, harga, komisi, stok, "
                    "merchant_id, kategori, deskripsi) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, nama.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, harga);
  sqlite3_bind_int(stmt, 3, komisi);
  sqlite3_bind_int(stmt, 4, stok);
  sqlite3_bind_int(stmt, 5, merchantID);
  sqlite3_bind_text(stmt, 6, kategori.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 7, deskripsi.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE;
}

// Update product
static bool NativeUpdateProduct(int productID, const std::string &nama,
                                int harga, int komisi, int stok,
                                const std::string &kategori,
                                const std::string &deskripsi) {
  if (g_db == nullptr)
    return false;

  const char *sql = "UPDATE products SET nama = ?, harga = ?, komisi = ?, stok "
                    "= ?, kategori = ?, deskripsi = ? WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_text(stmt, 1, nama.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, harga);
  sqlite3_bind_int(stmt, 3, komisi);
  sqlite3_bind_int(stmt, 4, stok);
  sqlite3_bind_text(stmt, 5, kategori.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 6, deskripsi.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 7, productID);

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
      "t.status, COALESCE(t.created_at, ''), "
      "COALESCE(u_cust.username, ''), COALESCE(u_courier.username, ''), "
      "COALESCE(p.nama, ''), COALESCE(p.harga, 0), "
      "COALESCE(u_cust.alamat, '') "
      "FROM transactions t "
      "INNER JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN users u_courier ON t.courier_id = u_courier.id "
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
    const char *custName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerName = custName ? custName : "";
    const char *courierName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.courierName = courierName ? courierName : "";
    const char *prodName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.productName = prodName ? prodName : "";
    trans.productPrice = sqlite3_column_int(stmt, 9);
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10));
    trans.customerAddress = custAddr ? custAddr : "";
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

  const char *sql = "SELECT id, nama, harga, komisi, stok, merchant_id, "
                    "COALESCE(kategori, ''), COALESCE(deskripsi, ''), "
                    "COALESCE(is_active, 1) FROM products "
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
    product.stok = sqlite3_column_int(stmt, 4);
    product.merchantID = sqlite3_column_int(stmt, 5);
    const char *kat =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    product.kategori = kat ? kat : "";
    const char *desk =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    product.deskripsi = desk ? desk : "";
    product.isActive = sqlite3_column_int(stmt, 8);
    products.push_back(product);
  }

  sqlite3_finalize(stmt);
  return products;
}

// Get all products with merchant name (for customer catalog)
static std::vector<ProductData> NativeGetAllProductsWithMerchantName() {
  std::vector<ProductData> products;
  if (g_db == nullptr)
    return products;

  const char *sql = "SELECT p.id, p.nama, p.harga, p.komisi, p.stok, "
                    "p.merchant_id, u.username, "
                    "COALESCE(p.kategori, ''), COALESCE(p.deskripsi, ''), "
                    "COALESCE(u.alamat, '') "
                    "FROM products p "
                    "LEFT JOIN users u ON p.merchant_id = u.id "
                    "WHERE COALESCE(p.is_active, 1) = 1 "
                    "ORDER BY p.id DESC;";
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
    product.stok = sqlite3_column_int(stmt, 4);
    product.merchantID = sqlite3_column_int(stmt, 5);
    const char *merchName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    product.merchantName = merchName ? merchName : "";
    const char *kat =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    product.kategori = kat ? kat : "";
    const char *desk =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    product.deskripsi = desk ? desk : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    product.merchantAlamat = merchAddr ? merchAddr : "";
    products.push_back(product);
  }

  sqlite3_finalize(stmt);
  return products;
}

// Frequently bought product row (product_id, name, merchant, count)
struct FrequentProductRow {
  int productID;
  std::string productName;
  std::string merchantName;
  int purchaseCount;
};

static std::vector<FrequentProductRow> NativeGetFrequentlyBoughtProducts() {
  std::vector<FrequentProductRow> rows;
  if (g_db == nullptr)
    return rows;

  const char *sql =
      "SELECT p.id, COALESCE(p.nama, ''), COALESCE(u.username, ''), "
      "COUNT(t.id) AS cnt FROM transactions t "
      "INNER JOIN products p ON t.product_id = p.id "
      "INNER JOIN users u ON p.merchant_id = u.id "
      "WHERE t.status != 'cancelled' "
      "GROUP BY t.product_id ORDER BY cnt DESC;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    return rows;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    FrequentProductRow r;
    r.productID = sqlite3_column_int(stmt, 0);
    const char *pn =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    r.productName = pn ? pn : "";
    const char *mn =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    r.merchantName = mn ? mn : "";
    r.purchaseCount = sqlite3_column_int(stmt, 3);
    rows.push_back(r);
  }

  sqlite3_finalize(stmt);
  return rows;
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
      const char *addr =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
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

// Get active express couriers
static std::vector<UserData> NativeGetExpressCouriers() {
  std::vector<UserData> couriers;
  if (g_db == nullptr)
    return couriers;

  const char *sql =
      "SELECT id, username FROM users WHERE role = 'Courier' AND "
      "courier_type = 'express' AND is_active = 1 ORDER BY username;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return couriers;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    UserData user;
    user.id = sqlite3_column_int(stmt, 0);
    const char *uname =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    user.username = uname ? uname : "";
    couriers.push_back(user);
  }

  sqlite3_finalize(stmt);
  return couriers;
}

// Purchase product - create transaction and handle money
static bool NativePurchaseProduct(int productID, int customerID,
                                  bool chargeOngkir,
                                  const std::string &shippingType = "regular",
                                  int courierID = 0) {
  if (g_db == nullptr)
    return false;

  // Get product info
  const char *sqlProduct =
      "SELECT harga, komisi, stok, merchant_id FROM products WHERE id = ?;";
  sqlite3_stmt *stmt;
  int harga = 0, komisi = 0, stok = 0, merchantID = 0;

  if (sqlite3_prepare_v2(g_db, sqlProduct, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      harga = sqlite3_column_int(stmt, 0);
      komisi = sqlite3_column_int(stmt, 1);
      stok = sqlite3_column_int(stmt, 2);
      merchantID = sqlite3_column_int(stmt, 3);
    }
    sqlite3_finalize(stmt);
  }

  if (harga == 0 || merchantID == 0)
    return false;

  // Check stock
  if (stok <= 0)
    return false;

  // Get all active Admin IDs
  std::vector<int> adminIDs;
  const char *sqlAdmin =
      "SELECT id FROM users WHERE role = 'Admin' AND COALESCE(is_active, 1) = "
      "1 ORDER BY id ASC;";
  if (sqlite3_prepare_v2(g_db, sqlAdmin, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      adminIDs.push_back(sqlite3_column_int(stmt, 0));
    }
    sqlite3_finalize(stmt);
  }

  // Calculate total with shipping fee (ongkir) - only if chargeOngkir is true
  int ongkir = chargeOngkir ? 10000 : 0;
  int totalCharge = harga + ongkir;

  // Check customer saldo (harga + ongkir)
  int saldo = NativeGetUserSaldo(customerID);
  if (saldo < totalCharge)
    return false;

  // Begin transaction
  ExecuteSQL("BEGIN TRANSACTION;");

  // Deduct customer saldo (harga + ongkir)
  if (!NativeUpdateUserSaldo(customerID, saldo - totalCharge)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Decrement stock
  const char *sqlStock =
      "UPDATE products SET stok = stok - 1 WHERE id = ? AND stok > 0;";
  if (sqlite3_prepare_v2(g_db, sqlStock, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE || sqlite3_changes(g_db) == 0) {
      ExecuteSQL("ROLLBACK;");
      return false;
    }
  } else {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Calculate commissions
  int appCommission = harga * komisi / 100;
  int merchantIncome = harga - appCommission;

  // Update merchant saldo
  int merchantSaldo = NativeGetUserSaldo(merchantID);
  if (!NativeUpdateUserSaldo(merchantID, merchantSaldo + merchantIncome)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Distribute commission equally to all active admins
  if (!adminIDs.empty() && appCommission > 0) {
    int adminCount = (int)adminIDs.size();
    int perAdmin = appCommission / adminCount;
    int remainder = appCommission % adminCount;

    for (int i = 0; i < adminCount; i++) {
      int share = perAdmin + (i == 0 ? remainder : 0);
      if (share <= 0)
        continue;
      int adminSaldo = NativeGetUserSaldo(adminIDs[i]);
      if (!NativeUpdateUserSaldo(adminIDs[i], adminSaldo + share)) {
        ExecuteSQL("ROLLBACK;");
        return false;
      }
    }
  }

  // Ensure courier_id column exists
  ExecuteSQL("ALTER TABLE transactions ADD COLUMN courier_id INTEGER;");

  // Create transaction
  const char *sqlTrans =
      courierID > 0
          ? "INSERT INTO transactions (product_id, customer_id, status, "
            "shipping_type, affiliate_id, courier_id) VALUES (?, ?, 'pending', "
            "?, ?, ?);"
          : "INSERT INTO transactions (product_id, customer_id, status, "
            "shipping_type) VALUES (?, ?, 'pending', ?);";
  int transID = 0;

  if (sqlite3_prepare_v2(g_db, sqlTrans, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    sqlite3_bind_int(stmt, 2, customerID);
    sqlite3_bind_text(stmt, 3, shippingType.c_str(), -1, SQLITE_TRANSIENT);
    if (courierID > 0) {
      sqlite3_bind_int(stmt, 4, courierID);
      sqlite3_bind_int(stmt, 5, courierID);
    }
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
      ExecuteSQL("ROLLBACK;");
      return false;
    }
    transID = (int)sqlite3_last_insert_rowid(g_db);
  } else {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Add income record for merchant
  const char *sqlIncomeMerchant =
      "INSERT INTO income (user_id, transaction_id, amount, type, description) "
      "VALUES (?, ?, ?, 'sale', 'Penjualan produk');";
  if (sqlite3_prepare_v2(g_db, sqlIncomeMerchant, -1, &stmt, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    sqlite3_bind_int(stmt, 2, transID);
    sqlite3_bind_int(stmt, 3, merchantIncome);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // Add income records for each active admin
  if (!adminIDs.empty() && appCommission > 0) {
    int adminCount = (int)adminIDs.size();
    int perAdmin = appCommission / adminCount;
    int remainder = appCommission % adminCount;

    for (int i = 0; i < adminCount; i++) {
      int share = perAdmin + (i == 0 ? remainder : 0);
      if (share <= 0)
        continue;
      const char *sqlIncomeAdmin =
          "INSERT INTO income (user_id, transaction_id, amount, type, "
          "description) "
          "VALUES (?, ?, ?, 'commission', 'Komisi aplikasi');";
      if (sqlite3_prepare_v2(g_db, sqlIncomeAdmin, -1, &stmt, nullptr) ==
          SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, adminIDs[i]);
        sqlite3_bind_int(stmt, 2, transID);
        sqlite3_bind_int(stmt, 3, share);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
      }
    }
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

  const char *sql =
      "SELECT t.id, t.product_id, t.customer_id, COALESCE(t.courier_id, "
      "0), t.status, COALESCE(t.created_at, ''), "
      "COALESCE(u_courier.username, ''), COALESCE(p.harga, 0), "
      "COALESCE(p.nama, ''), "
      "COALESCE(u_merch.alamat, ''), COALESCE(u_cust.alamat, ''), "
      "COALESCE(t.shipping_type, 'regular') "
      "FROM transactions t "
      "LEFT JOIN users u_courier ON t.courier_id = u_courier.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "WHERE t.customer_id = ? ORDER BY t.id DESC;";
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
    const char *courierName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.courierName = courierName ? courierName : "";
    trans.totalPrice = sqlite3_column_int(stmt, 7);
    const char *productName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.productName = productName ? productName : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10));
    trans.customerAddress = custAddr ? custAddr : "";
    const char *shipType =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 11));
    trans.shippingType = shipType ? shipType : "regular";
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Customer confirms delivery received - updates status to 'completed'
static bool NativeConfirmDelivery(int transactionID, int customerID) {
  if (g_db == nullptr)
    return false;

  const char *sql =
      "UPDATE transactions SET status = 'completed' "
      "WHERE id = ? AND customer_id = ? AND status = 'delivered';";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_int(stmt, 2, customerID);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return rc == SQLITE_DONE && sqlite3_changes(g_db) > 0;
}

// Withdraw saldo - for couriers and merchants
static bool NativeWithdrawSaldo(int userID, int amount) {
  if (g_db == nullptr)
    return false;

  // Check current saldo
  int currentSaldo = NativeGetUserSaldo(userID);
  if (currentSaldo < amount)
    return false;

  // Deduct saldo
  if (!NativeUpdateUserSaldo(userID, currentSaldo - amount))
    return false;

  // Record withdrawal in income table
  const char *sqlIncome =
      "INSERT INTO income (user_id, transaction_id, amount, type, description) "
      "VALUES (?, 0, ?, 'withdrawal', 'Penarikan saldo');";
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(g_db, sqlIncome, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, userID);
    sqlite3_bind_int(stmt, 2, -amount);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  return true;
}

// Cancel order and refund customer
static bool NativeCancelOrder(int transactionID, int customerID) {
  if (g_db == nullptr)
    return false;

  // Get transaction details
  const char *sqlGetTrans =
      "SELECT t.product_id, t.customer_id, t.status, p.harga, p.komisi, "
      "p.merchant_id "
      "FROM transactions t "
      "INNER JOIN products p ON t.product_id = p.id "
      "WHERE t.id = ? AND t.customer_id = ?;";
  sqlite3_stmt *stmt;

  int productID = 0, custID = 0, harga = 0, komisi = 0, merchantID = 0;
  std::string status;

  int rc = sqlite3_prepare_v2(g_db, sqlGetTrans, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_int(stmt, 2, customerID);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    productID = sqlite3_column_int(stmt, 0);
    custID = sqlite3_column_int(stmt, 1);
    const char *stat =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    status = stat ? stat : "";
    harga = sqlite3_column_int(stmt, 3);
    komisi = sqlite3_column_int(stmt, 4);
    merchantID = sqlite3_column_int(stmt, 5);
  }
  sqlite3_finalize(stmt);

  // Only allow canceling pending orders
  if (status != "pending")
    return false;

  // Begin transaction
  ExecuteSQL("BEGIN TRANSACTION;");

  // Refund customer (harga + ongkir)
  int ongkir = 10000;
  int refundAmount = harga + ongkir;
  int customerSaldo = NativeGetUserSaldo(customerID);
  if (!NativeUpdateUserSaldo(customerID, customerSaldo + refundAmount)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Restore stock
  const char *sqlRestoreStock =
      "UPDATE products SET stok = stok + 1 WHERE id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlRestoreStock, -1, &stmt, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // Reverse merchant income
  int merchantIncome = harga - (harga * komisi / 100);
  int merchantSaldo = NativeGetUserSaldo(merchantID);
  if (!NativeUpdateUserSaldo(merchantID, merchantSaldo - merchantIncome)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // Delete income record for merchant
  const char *sqlDeleteIncome =
      "DELETE FROM income WHERE transaction_id = ? AND user_id = ? AND type = "
      "'sale';";
  if (sqlite3_prepare_v2(g_db, sqlDeleteIncome, -1, &stmt, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    sqlite3_bind_int(stmt, 2, merchantID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // Update transaction status to cancelled
  const char *sqlUpdate =
      "UPDATE transactions SET status = 'cancelled' WHERE id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlUpdate, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
      ExecuteSQL("ROLLBACK;");
      return false;
    }
  }

  ExecuteSQL("COMMIT;");
  return true;
}

// ============ Courier Functions ============

// Add courier_id column if not exists
static void EnsureCourierColumn() {
  ExecuteSQL("ALTER TABLE transactions ADD COLUMN courier_id INTEGER;");
}

// Get courier type for a user
static std::string NativeGetUserCourierType(int userID) {
  if (g_db == nullptr)
    return "regular";

  const char *sql =
      "SELECT COALESCE(courier_type, 'regular') FROM users WHERE id = ?;";
  sqlite3_stmt *stmt;
  std::string courierType = "regular";

  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, userID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      const char *ct =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      courierType = ct ? ct : "regular";
    }
    sqlite3_finalize(stmt);
  }
  return courierType;
}

// Get pending deliveries filtered by courier type
// Regular couriers: only see regular orders (no courier assigned)
// Express couriers: see regular orders + express orders assigned to them
static std::vector<TransactionData>
NativeGetPendingDeliveries(int courierID, const std::string &courierType) {
  std::vector<TransactionData> transactions;
  if (g_db == nullptr)
    return transactions;

  EnsureCourierColumn();

  std::string sqlStr;
  if (courierType == "express") {
    // Express courier sees: regular unclaimed + express assigned to them
    sqlStr =
        "SELECT t.id, t.product_id, t.customer_id, COALESCE(t.courier_id, 0), "
        "t.status, COALESCE(t.created_at, ''), "
        "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, ''), "
        "COALESCE(u_cust.username, ''), "
        "COALESCE(p.nama, ''), COALESCE(p.harga, 0) "
        "FROM transactions t "
        "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
        "LEFT JOIN products p ON t.product_id = p.id "
        "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
        "WHERE t.status = 'pending' AND ("
        "  ((t.courier_id IS NULL OR t.courier_id = 0) AND "
        "   COALESCE(t.shipping_type, 'regular') = 'regular')"
        "  OR "
        "  (t.courier_id = " +
        std::to_string(courierID) +
        " AND COALESCE(t.shipping_type, 'regular') = 'express')"
        ") ORDER BY u_cust.username, t.id DESC;";
  } else {
    // Regular courier: only regular orders with no courier
    sqlStr = "SELECT t.id, t.product_id, t.customer_id, 0, t.status, "
             "COALESCE(t.created_at, ''), "
             "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, ''), "
             "COALESCE(u_cust.username, ''), "
             "COALESCE(p.nama, ''), COALESCE(p.harga, 0) "
             "FROM transactions t "
             "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
             "LEFT JOIN products p ON t.product_id = p.id "
             "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
             "WHERE t.status = 'pending' AND (t.courier_id IS NULL OR "
             "t.courier_id = 0) AND COALESCE(t.shipping_type, 'regular') = "
             "'regular' "
             "ORDER BY u_cust.username, t.id DESC;";
  }

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sqlStr.c_str(), -1, &stmt, nullptr);
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
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    const char *custName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.customerName = custName ? custName : "";
    const char *prodName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    trans.productName = prodName ? prodName : "";
    trans.productPrice = sqlite3_column_int(stmt, 10);
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
      "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, ''), "
      "COALESCE(u_cust.username, ''), "
      "COALESCE(p.nama, ''), COALESCE(p.harga, 0) "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "WHERE t.courier_id = ? AND t.status = 'shipping' "
      "ORDER BY u_cust.username, t.id DESC;";
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
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    const char *custName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.customerName = custName ? custName : "";
    const char *prodName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    trans.productName = prodName ? prodName : "";
    trans.productPrice = sqlite3_column_int(stmt, 10);
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
      "COALESCE(u_cust.alamat, ''), COALESCE(u_merch.alamat, ''), "
      "COALESCE(u_cust.username, ''), "
      "COALESCE(p.nama, ''), COALESCE(p.harga, 0) "
      "FROM transactions t "
      "LEFT JOIN users u_cust ON t.customer_id = u_cust.id "
      "LEFT JOIN products p ON t.product_id = p.id "
      "LEFT JOIN users u_merch ON p.merchant_id = u_merch.id "
      "WHERE t.courier_id = ? AND t.status = 'delivered' "
      "ORDER BY u_cust.username, t.id DESC;";
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
    const char *custAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
    trans.customerAddress = custAddr ? custAddr : "";
    const char *merchAddr =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
    trans.merchantAddress = merchAddr ? merchAddr : "";
    const char *custName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
    trans.customerName = custName ? custName : "";
    const char *prodName =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
    trans.productName = prodName ? prodName : "";
    trans.productPrice = sqlite3_column_int(stmt, 10);
    transactions.push_back(trans);
  }

  sqlite3_finalize(stmt);
  return transactions;
}

// Claim delivery (courier takes the order)
// Allow: unclaimed orders (courier_id IS NULL/0) OR express orders already
// assigned to this courier (courier_id = courierID AND status = 'pending')
static bool NativeClaimDelivery(int transactionID, int courierID) {
  if (g_db == nullptr)
    return false;

  const char *sql =
      "UPDATE transactions SET courier_id = ?, status = 'shipping' "
      "WHERE id = ? AND ("
      "  (courier_id IS NULL OR courier_id = 0) OR "
      "  (courier_id = ? AND status = 'pending')"
      ");";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;

  sqlite3_bind_int(stmt, 1, courierID);
  sqlite3_bind_int(stmt, 2, transactionID);
  sqlite3_bind_int(stmt, 3, courierID);

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

// ============ Product Deactivation & Notifications ============

struct NotificationData {
  int id;
  std::string message;
  std::string reason;
  std::string createdAt;
  int isRead;
};

// Deactivate a product and notify the merchant
static bool NativeDeactivateProduct(int productID, const std::string &reason) {
  if (g_db == nullptr)
    return false;

  // Get merchant_id and product name
  const char *sqlGet = "SELECT merchant_id, nama FROM products WHERE id = ?;";
  sqlite3_stmt *stmt;
  int merchantID = 0;
  std::string productName;

  if (sqlite3_prepare_v2(g_db, sqlGet, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      merchantID = sqlite3_column_int(stmt, 0);
      const char *n =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      productName = n ? n : "";
    }
    sqlite3_finalize(stmt);
  }

  if (merchantID == 0)
    return false;

  // Set is_active = 0
  const char *sqlDeact = "UPDATE products SET is_active = 0 WHERE id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlDeact, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // Insert notification for merchant
  std::string msg =
      "Produk '" + productName + "' telah dinonaktifkan oleh Admin.";
  const char *sqlNotif =
      "INSERT INTO notifications (user_id, message, reason) VALUES (?, ?, ?);";
  if (sqlite3_prepare_v2(g_db, sqlNotif, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    sqlite3_bind_text(stmt, 2, msg.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, reason.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  return true;
}

// Activate a product
static bool NativeActivateProduct(int productID) {
  if (g_db == nullptr)
    return false;
  const char *sql = "UPDATE products SET is_active = 1 WHERE id = ?;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, productID);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE;
}

// Get unread notifications for a user
static std::vector<NotificationData> NativeGetNotifications(int userID) {
  std::vector<NotificationData> notifs;
  if (g_db == nullptr)
    return notifs;

  const char *sql = "SELECT id, message, COALESCE(reason, ''), "
                    "COALESCE(created_at, ''), is_read "
                    "FROM notifications WHERE user_id = ? ORDER BY id DESC;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, userID);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      NotificationData n;
      n.id = sqlite3_column_int(stmt, 0);
      const char *msg =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      n.message = msg ? msg : "";
      const char *rsn =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      n.reason = rsn ? rsn : "";
      const char *ca =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
      n.createdAt = ca ? ca : "";
      n.isRead = sqlite3_column_int(stmt, 4);
      notifs.push_back(n);
    }
    sqlite3_finalize(stmt);
  }
  return notifs;
}

// Mark all notifications as read for a user
static bool NativeMarkNotificationsRead(int userID) {
  if (g_db == nullptr)
    return false;
  const char *sql =
      "UPDATE notifications SET is_read = 1 WHERE user_id = ? AND is_read = 0;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, userID);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE;
}

// ============ Refund Functions ============

// Full refund: reverse all financial effects of a transaction
static bool NativeRefundOrder(int transactionID) {
  if (g_db == nullptr)
    return false;

  // Get transaction details
  const char *sqlGet =
      "SELECT t.product_id, t.customer_id, COALESCE(t.courier_id, 0), "
      "t.status, p.harga, p.komisi, p.merchant_id "
      "FROM transactions t "
      "JOIN products p ON t.product_id = p.id "
      "WHERE t.id = ?;";
  sqlite3_stmt *stmt;

  int productID = 0, customerID = 0, courierID = 0, harga = 0, komisi = 0,
      merchantID = 0;
  std::string status;

  int rc = sqlite3_prepare_v2(g_db, sqlGet, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, transactionID);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    productID = sqlite3_column_int(stmt, 0);
    customerID = sqlite3_column_int(stmt, 1);
    courierID = sqlite3_column_int(stmt, 2);
    const char *s =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    status = s ? s : "";
    harga = sqlite3_column_int(stmt, 4);
    komisi = sqlite3_column_int(stmt, 5);
    merchantID = sqlite3_column_int(stmt, 6);
  }
  sqlite3_finalize(stmt);

  // Only allow refund for shipping/delivered/refund_requested
  if (status != "shipping" && status != "delivered" &&
      status != "refund_requested")
    return false;

  ExecuteSQL("BEGIN TRANSACTION;");

  // 1. Refund customer (harga + ongkir)
  int ongkir = 10000;
  int refundAmount = harga + ongkir;
  int customerSaldo = NativeGetUserSaldo(customerID);
  if (!NativeUpdateUserSaldo(customerID, customerSaldo + refundAmount)) {
    ExecuteSQL("ROLLBACK;");
    return false;
  }

  // 2. Reverse merchant income
  int merchantIncome = harga - (harga * komisi / 100);
  int merchantSaldo = NativeGetUserSaldo(merchantID);
  NativeUpdateUserSaldo(merchantID, merchantSaldo - merchantIncome);

  // 3. Reverse courier income (if delivery was completed)
  if (courierID > 0 && status == "delivered") {
    int deliveryFee = 10000;
    int courierSaldo = NativeGetUserSaldo(courierID);
    NativeUpdateUserSaldo(courierID, courierSaldo - deliveryFee);
  }

  // 4. Restore stock
  const char *sqlStock = "UPDATE products SET stok = stok + 1 WHERE id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlStock, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // 5. Delete income records for this transaction
  const char *sqlDelIncome = "DELETE FROM income WHERE transaction_id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlDelIncome, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  // 6. Update transaction status to 'refunded'
  const char *sqlUpdate =
      "UPDATE transactions SET status = 'refunded' WHERE id = ?;";
  if (sqlite3_prepare_v2(g_db, sqlUpdate, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
      ExecuteSQL("ROLLBACK;");
      return false;
    }
  }

  // 7. Notify merchant
  const char *sqlNotifMerch =
      "INSERT INTO notifications (user_id, message, reason) VALUES "
      "(?, 'Pesanan telah di-refund oleh Admin.', 'Barang tidak sampai');";
  if (sqlite3_prepare_v2(g_db, sqlNotifMerch, -1, &stmt, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, merchantID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }

  ExecuteSQL("COMMIT;");
  return true;
}

// Customer requests refund (changes status to refund_requested)
static bool NativeRequestRefund(int transactionID, int customerID) {
  if (g_db == nullptr)
    return false;

  const char *sql = "UPDATE transactions SET status = 'refund_requested' "
                    "WHERE id = ? AND customer_id = ? AND status = 'shipping' "
                    "AND julianday('now') - julianday(created_at) > 3;";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_int(stmt, 2, customerID);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE && sqlite3_changes(g_db) > 0;
}

// ============ Reviews ============

struct ReviewData {
  int id;
  int rating;
  std::string comment;
  std::string customerName;
  std::string createdAt;
};

static bool NativeAddReview(int transactionID, int customerID, int productID,
                            int rating, const std::string &comment) {
  if (g_db == nullptr)
    return false;
  const char *sql =
      "INSERT INTO reviews (transaction_id, customer_id, product_id, rating, "
      "comment) VALUES (?, ?, ?, ?, ?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_int(stmt, 2, customerID);
  sqlite3_bind_int(stmt, 3, productID);
  sqlite3_bind_int(stmt, 4, rating);
  sqlite3_bind_text(stmt, 5, comment.c_str(), -1, SQLITE_TRANSIENT);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE;
}

static double NativeGetAverageRating(int productID) {
  if (g_db == nullptr)
    return 0.0;
  const char *sql =
      "SELECT COALESCE(AVG(CAST(rating AS REAL)), 0) FROM reviews WHERE "
      "product_id = ?;";
  sqlite3_stmt *stmt;
  double avg = 0.0;
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, productID);
    if (sqlite3_step(stmt) == SQLITE_ROW)
      avg = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
  }
  return avg;
}

static bool NativeHasReviewed(int transactionID) {
  if (g_db == nullptr)
    return true;
  const char *sql = "SELECT COUNT(*) FROM reviews WHERE transaction_id = ?;";
  sqlite3_stmt *stmt;
  bool exists = true;
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    if (sqlite3_step(stmt) == SQLITE_ROW)
      exists = sqlite3_column_int(stmt, 0) > 0;
    sqlite3_finalize(stmt);
  }
  return exists;
}

// ============ Order Tracking ============

struct TrackingData {
  std::string status;
  std::string description;
  std::string createdAt;
};

static bool NativeAddTrackingEvent(int transactionID, const std::string &status,
                                   const std::string &description) {
  if (g_db == nullptr)
    return false;
  const char *sql = "INSERT INTO order_tracking (transaction_id, status, "
                    "description) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
    return false;
  sqlite3_bind_int(stmt, 1, transactionID);
  sqlite3_bind_text(stmt, 2, status.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_TRANSIENT);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE;
}

static std::vector<TrackingData> NativeGetOrderTracking(int transactionID) {
  std::vector<TrackingData> tracking;
  if (g_db == nullptr)
    return tracking;
  const char *sql = "SELECT status, description, "
                    "COALESCE(created_at, '') FROM order_tracking "
                    "WHERE transaction_id = ? ORDER BY id ASC;";
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, transactionID);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      TrackingData t;
      const char *s =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      t.status = s ? s : "";
      const char *d =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      t.description = d ? d : "";
      const char *c =
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      t.createdAt = c ? c : "";
      tracking.push_back(t);
    }
    sqlite3_finalize(stmt);
  }
  return tracking;
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

  // Register with courier_type
  static bool RegisterUser(String ^ username, String ^ password, String ^ role,
                           String ^ courierType) {
    std::string user = msclr::interop::marshal_as<std::string>(username);
    std::string pass = msclr::interop::marshal_as<std::string>(password);
    std::string r = msclr::interop::marshal_as<std::string>(role);
    std::string ct = msclr::interop::marshal_as<std::string>(courierType);

    return NativeRegisterUser(user, pass, r, ct);
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

  // Helper: Format user ID based on role
  static String ^ FormatUserID(int id, String ^ role) {
    if (role == "Admin")
      return "USRA" + id;
    if (role == "Merchant")
      return "USRM" + id;
    if (role == "Customer")
      return "USRC" + id;
    if (role == "Courier")
      return "USRK" + id;
    return "USR" + id;
  }

  // Get all users as DataTable for DataGridView
  static DataTable ^ GetAllUsersTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Username", String::typeid);
    dt->Columns->Add("_Password", String::typeid);
    dt->Columns->Add("Role", String::typeid);
    dt->Columns->Add("Saldo", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Alamat", String::typeid);

    std::vector<UserData> users = NativeGetAllUsers();
    for (const auto &user : users) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = user.id;
      String ^ role = gcnew String(user.role.c_str());
      row["ID"] = FormatUserID(user.id, role);
      row["Username"] = gcnew String(user.username.c_str());
      row["_Password"] = gcnew String(user.password.c_str());
      row["Role"] = role;
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

  // Update user (username and optionally password)
  static bool UpdateUser(int userID, String ^ newUsername,
                         String ^ newPassword) {
    std::string uname = msclr::interop::marshal_as<std::string>(newUsername);
    std::string pass =
        (newPassword != nullptr && newPassword->Length > 0)
            ? msclr::interop::marshal_as<std::string>(newPassword)
            : "";
    return NativeUpdateUser(userID, uname, pass);
  }

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
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Username", String::typeid);
    dt->Columns->Add("Amount", Int32::typeid);
    dt->Columns->Add("Type", String::typeid);
    dt->Columns->Add("Description", String::typeid);
    dt->Columns->Add("Date", String::typeid);

    std::vector<IncomeData> incomes = NativeGetAllIncome();
    for (const auto &income : incomes) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = income.id;
      row["ID"] = "INC" + income.id;
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
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("Pembeli", String::typeid);
    dt->Columns->Add("Kurir", String::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Lokasi Toko", String::typeid);
    dt->Columns->Add("Lokasi Pembeli", String::typeid);

    std::vector<TransactionData> transactions = NativeGetAllTransactions();
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["ID"] = "TRN" + trans.transID;
      row["ProductID"] = trans.productID;
      row["Pembeli"] = gcnew String(trans.customerName.c_str());
      row["Kurir"] = gcnew String(trans.courierName.c_str());
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      row["Lokasi Toko"] = gcnew String(trans.merchantAddress.c_str());
      row["Lokasi Pembeli"] = gcnew String(trans.customerAddress.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Update transaction status
  static bool UpdateTransactionStatus(int transactionID, String ^ newStatus) {
    if (g_db == nullptr)
      return false;

    std::string statusNative =
        msclr::interop::marshal_as<std::string>(newStatus);

    const char *sql = "UPDATE transactions SET status = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
      return false;

    sqlite3_bind_text(stmt, 1, statusNative.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, transactionID);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
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
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Nama", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Komisi", Int32::typeid);
    dt->Columns->Add("Stok", Int32::typeid);
    dt->Columns->Add("Kategori", String::typeid);
    dt->Columns->Add("Deskripsi", String::typeid);

    std::vector<ProductData> products = NativeGetProductsByMerchant(merchantID);
    for (const auto &product : products) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = product.id;
      row["ID"] = "PRD" + product.id;
      row["Nama"] = gcnew String(product.nama.c_str());
      row["Harga"] = product.harga;
      row["Komisi"] = product.komisi;
      row["Stok"] = product.stok;
      row["Kategori"] = gcnew String(product.kategori.c_str());
      row["Deskripsi"] = gcnew String(product.deskripsi.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Add new product
  static bool AddProduct(String ^ nama, int harga, int komisi, int stok,
                         int merchantID, String ^ kategori,
                         String ^ deskripsi) {
    std::string namaNative = msclr::interop::marshal_as<std::string>(nama);
    std::string katNative = msclr::interop::marshal_as<std::string>(kategori);
    std::string deskNative = msclr::interop::marshal_as<std::string>(deskripsi);
    return NativeAddProduct(namaNative, harga, komisi, stok, merchantID,
                            katNative, deskNative);
  }

  // Update product
  static bool UpdateProduct(int productID, String ^ nama, int harga, int komisi,
                            int stok, String ^ kategori, String ^ deskripsi) {
    std::string namaNative = msclr::interop::marshal_as<std::string>(nama);
    std::string katNative = msclr::interop::marshal_as<std::string>(kategori);
    std::string deskNative = msclr::interop::marshal_as<std::string>(deskripsi);
    return NativeUpdateProduct(productID, namaNative, harga, komisi, stok,
                               katNative, deskNative);
  }

  // Delete product
  static bool DeleteProduct(int productID) {
    return NativeDeleteProduct(productID);
  }

  // Get transactions by merchant as DataTable
  static DataTable ^ GetTransactionsByMerchant(int merchantID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("Produk", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Pembeli", String::typeid);
    dt->Columns->Add("Kurir", String::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Pembeli", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetTransactionsByMerchant(merchantID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["ID"] = "TRN" + trans.transID;
      row["ProductID"] = trans.productID;
      row["Produk"] = gcnew String(trans.productName.c_str());
      row["Harga"] = trans.productPrice;
      row["Pembeli"] = gcnew String(trans.customerName.c_str());
      row["Kurir"] = gcnew String(trans.courierName.c_str());
      row["Status"] = gcnew String(trans.status.c_str());
      row["Date"] = gcnew String(trans.createdAt.c_str());
      row["Alamat Pembeli"] = gcnew String(trans.customerAddress.c_str());
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

      // Get all products as DataTable (for admin)
      static DataTable
      ^ GetAllProductsTable() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Nama", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Komisi", Int32::typeid);
    dt->Columns->Add("Stok", Int32::typeid);
    dt->Columns->Add("MerchantID", Int32::typeid);
    dt->Columns->Add("Kategori", String::typeid);
    dt->Columns->Add("Deskripsi", String::typeid);
    dt->Columns->Add("Status", String::typeid);

    std::vector<ProductData> products = NativeGetAllProducts();
    for (const auto &product : products) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = product.id;
      row["ID"] = "PRD" + product.id;
      row["Nama"] = gcnew String(product.nama.c_str());
      row["Harga"] = product.harga;
      row["Komisi"] = product.komisi;
      row["Stok"] = product.stok;
      row["MerchantID"] = product.merchantID;
      row["Kategori"] = gcnew String(product.kategori.c_str());
      row["Deskripsi"] = gcnew String(product.deskripsi.c_str());
      row["Status"] = product.isActive ? L"Aktif" : L"Nonaktif";
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get all products with merchant name as DataTable (for customer catalog)
  static DataTable ^ GetAllProductsWithMerchantName() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Nama", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Stok", Int32::typeid);
    dt->Columns->Add("Toko", String::typeid);
    dt->Columns->Add("Lokasi Toko", String::typeid);
    dt->Columns->Add("MerchantID", Int32::typeid);
    dt->Columns->Add("Komisi", Int32::typeid);
    dt->Columns->Add("Kategori", String::typeid);
    dt->Columns->Add("Deskripsi", String::typeid);

    std::vector<ProductData> products = NativeGetAllProductsWithMerchantName();
    for (const auto &product : products) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = product.id;
      row["ID"] = "PRD" + product.id;
      row["Nama"] = gcnew String(product.nama.c_str());
      row["Harga"] = product.harga;
      row["Stok"] = product.stok;
      row["Toko"] = gcnew String(product.merchantName.c_str());
      row["Lokasi Toko"] = gcnew String(product.merchantAlamat.c_str());
      row["MerchantID"] = product.merchantID;
      row["Komisi"] = product.komisi;
      row["Kategori"] = gcnew String(product.kategori.c_str());
      row["Deskripsi"] = gcnew String(product.deskripsi.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Get frequently bought products (for admin tab)
  static DataTable ^ GetFrequentlyBoughtProducts() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("No", Int32::typeid);
    dt->Columns->Add("ID Produk", String::typeid);
    dt->Columns->Add("Nama Produk", String::typeid);
    dt->Columns->Add("Toko", String::typeid);
    dt->Columns->Add("Jumlah Dibeli", Int32::typeid);

    std::vector<FrequentProductRow> rows =
        NativeGetFrequentlyBoughtProducts();
    int no = 1;
    for (const auto &r : rows) {
      DataRow ^ row = dt->NewRow();
      row["No"] = no++;
      row["ID Produk"] = "PRD" + r.productID;
      row["Nama Produk"] = gcnew String(r.productName.c_str());
      row["Toko"] = gcnew String(r.merchantName.c_str());
      row["Jumlah Dibeli"] = r.purchaseCount;
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
  static bool PurchaseProduct(int productID, int customerID,
                              bool chargeOngkir) {
    return NativePurchaseProduct(productID, customerID, chargeOngkir);
  }

  // Purchase product with shipping type and courier
  static bool PurchaseProduct(int productID, int customerID, bool chargeOngkir,
                              String ^ shippingType, int courierID) {
    std::string st = msclr::interop::marshal_as<std::string>(shippingType);
    return NativePurchaseProduct(productID, customerID, chargeOngkir, st,
                                 courierID);
  }

  // Get active express couriers
  static DataTable ^ GetExpressCouriers() {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("ID", Int32::typeid);
    dt->Columns->Add("Username", String::typeid);

    std::vector<UserData> couriers = NativeGetExpressCouriers();
    for (const auto &courier : couriers) {
      DataRow ^ row = dt->NewRow();
      row["ID"] = courier.id;
      row["Username"] = gcnew String(courier.username.c_str());
      dt->Rows->Add(row);
    }
    return dt;
  }

  // Get transactions by customer as DataTable
  static DataTable ^ GetTransactionsByCustomer(int customerID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("_RawProductID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("Produk", String::typeid);
    dt->Columns->Add("Total", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Kurir", String::typeid);
    dt->Columns->Add("Tanggal", String::typeid);
    dt->Columns->Add("Lokasi Toko", String::typeid);
    dt->Columns->Add("Lokasi Pembeli", String::typeid);
    dt->Columns->Add("Tipe Pengiriman", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetTransactionsByCustomer(customerID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["_RawProductID"] = trans.productID;
      row["ID"] = "TRN" + trans.transID;
      row["Produk"] = gcnew String(trans.productName.c_str());
      row["Total"] = trans.totalPrice;
      row["Status"] = gcnew String(trans.status.c_str());
      row["Kurir"] = gcnew String(trans.courierName.c_str());
      row["Tanggal"] = gcnew String(trans.createdAt.c_str());
      row["Lokasi Toko"] = gcnew String(trans.merchantAddress.c_str());
      row["Lokasi Pembeli"] = gcnew String(trans.customerAddress.c_str());
      row["Tipe Pengiriman"] = gcnew String(trans.shippingType.c_str());
      dt->Rows->Add(row);
    }

    return dt;
  }

  // Confirm delivery received by customer
  static bool ConfirmDelivery(int transactionID, int customerID) {
    return NativeConfirmDelivery(transactionID, customerID);
  }

  // Withdraw saldo for couriers and merchants
  static bool WithdrawSaldo(int userID, int amount) {
    return NativeWithdrawSaldo(userID, amount);
  }

  // Cancel order and refund customer
  static bool CancelOrder(int transactionID, int customerID) {
    return NativeCancelOrder(transactionID, customerID);
  }

  // ============ Courier Functions ============

  // Get courier type for a user
  static String ^ GetUserCourierType(int userID) {
    std::string ct = NativeGetUserCourierType(userID);
    return gcnew String(ct.c_str());
  }

  // Get pending deliveries as DataTable (filtered by courier type)
  static DataTable ^ GetPendingDeliveries(int courierID, String ^ courierType) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Pembeli", String::typeid);
    dt->Columns->Add("Produk", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    // Convert managed string to native
    std::string nativeCourierType = "regular";
    if (courierType != nullptr) {
      IntPtr ptr =
          Runtime::InteropServices::Marshal::StringToHGlobalAnsi(courierType);
      nativeCourierType = static_cast<const char *>(ptr.ToPointer());
      Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
    }

    std::vector<TransactionData> transactions =
        NativeGetPendingDeliveries(courierID, nativeCourierType);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["ID"] = "TRN" + trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Pembeli"] = gcnew String(trans.customerName.c_str());
      row["Produk"] = gcnew String(trans.productName.c_str());
      row["Harga"] = trans.productPrice;
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
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Pembeli", String::typeid);
    dt->Columns->Add("Produk", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetActiveDeliveries(courierID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["ID"] = "TRN" + trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Pembeli"] = gcnew String(trans.customerName.c_str());
      row["Produk"] = gcnew String(trans.productName.c_str());
      row["Harga"] = trans.productPrice;
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
    dt->Columns->Add("_RawID", Int32::typeid);
    dt->Columns->Add("ID", String::typeid);
    dt->Columns->Add("ProductID", Int32::typeid);
    dt->Columns->Add("CustomerID", Int32::typeid);
    dt->Columns->Add("Pembeli", String::typeid);
    dt->Columns->Add("Produk", String::typeid);
    dt->Columns->Add("Harga", Int32::typeid);
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Date", String::typeid);
    dt->Columns->Add("Alamat Customer", String::typeid);
    dt->Columns->Add("Alamat Merchant", String::typeid);

    std::vector<TransactionData> transactions =
        NativeGetDeliveryHistory(courierID);
    for (const auto &trans : transactions) {
      DataRow ^ row = dt->NewRow();
      row["_RawID"] = trans.transID;
      row["ID"] = "TRN" + trans.transID;
      row["ProductID"] = trans.productID;
      row["CustomerID"] = trans.customerID;
      row["Pembeli"] = gcnew String(trans.customerName.c_str());
      row["Produk"] = gcnew String(trans.productName.c_str());
      row["Harga"] = trans.productPrice;
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
  static array<int> ^
      GetCourierStats(int courierID) {
        CourierStats stats = NativeGetCourierStats(courierID);
        array<int> ^ result = gcnew array<int>(3);
        result[0] = stats.todayDeliveries;
        result[1] = stats.totalDeliveries;
        result[2] = stats.totalIncome;
        return result;
      }

      // Delete transaction (admin)
      static bool DeleteTransaction(int transactionID) {
    if (g_db == nullptr)
      return false;

    // First delete related income records
    const char *sqlIncome = "DELETE FROM income WHERE transaction_id = ?;";
    sqlite3_stmt *stmtIncome;

    int rc = sqlite3_prepare_v2(g_db, sqlIncome, -1, &stmtIncome, nullptr);
    if (rc == SQLITE_OK) {
      sqlite3_bind_int(stmtIncome, 1, transactionID);
      sqlite3_step(stmtIncome);
      sqlite3_finalize(stmtIncome);
    }

    // Then delete the transaction
    const char *sql = "DELETE FROM transactions WHERE id = ?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(g_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
      return false;

    sqlite3_bind_int(stmt, 1, transactionID);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
  }

  // ============ Product Deactivation ============

  static bool DeactivateProduct(int productID, String ^ reason) {
    std::string nativeReason = "";
    if (reason != nullptr) {
      IntPtr ptr =
          Runtime::InteropServices::Marshal::StringToHGlobalAnsi(reason);
      nativeReason = static_cast<const char *>(ptr.ToPointer());
      Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
    }
    return NativeDeactivateProduct(productID, nativeReason);
  }

  static bool ActivateProduct(int productID) {
    return NativeActivateProduct(productID);
  }

  // ============ Notifications ============

  static DataTable ^ GetNotifications(int userID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("Pesan", String::typeid);
    dt->Columns->Add("Alasan", String::typeid);
    dt->Columns->Add("Tanggal", String::typeid);
    dt->Columns->Add("Status", String::typeid);

    std::vector<NotificationData> notifs = NativeGetNotifications(userID);
    for (const auto &n : notifs) {
      DataRow ^ row = dt->NewRow();
      row["Pesan"] = gcnew String(n.message.c_str());
      row["Alasan"] = gcnew String(n.reason.c_str());
      row["Tanggal"] = gcnew String(n.createdAt.c_str());
      row["Status"] = n.isRead ? L"Dibaca" : L"Baru";
      dt->Rows->Add(row);
    }
    return dt;
  }

  static int GetUnreadNotificationCount(int userID) {
    std::vector<NotificationData> notifs = NativeGetNotifications(userID);
    int count = 0;
    for (const auto &n : notifs) {
      if (n.isRead == 0)
        count++;
    }
    return count;
  }

  static bool MarkNotificationsRead(int userID) {
    return NativeMarkNotificationsRead(userID);
  }

  // ============ Refund ============

  static bool RefundOrder(int transactionID) {
    return NativeRefundOrder(transactionID);
  }

  static bool RequestRefund(int transactionID, int customerID) {
    return NativeRequestRefund(transactionID, customerID);
  }

  // ============ Reviews ============

  static bool AddReview(int transactionID, int customerID, int productID,
                        int rating, String ^ comment) {
    std::string nativeComment = "";
    if (comment != nullptr) {
      IntPtr ptr =
          Runtime::InteropServices::Marshal::StringToHGlobalAnsi(comment);
      nativeComment = static_cast<const char *>(ptr.ToPointer());
      Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
    }
    return NativeAddReview(transactionID, customerID, productID, rating,
                           nativeComment);
  }

  static double GetAverageRating(int productID) {
    return NativeGetAverageRating(productID);
  }

  static bool HasReviewed(int transactionID) {
    return NativeHasReviewed(transactionID);
  }

  // ============ Order Tracking ============

  static bool AddTrackingEvent(int transactionID, String ^ status,
                               String ^ description) {
    std::string nStatus = "";
    std::string nDesc = "";
    if (status != nullptr) {
      IntPtr ptr =
          Runtime::InteropServices::Marshal::StringToHGlobalAnsi(status);
      nStatus = static_cast<const char *>(ptr.ToPointer());
      Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
    }
    if (description != nullptr) {
      IntPtr ptr =
          Runtime::InteropServices::Marshal::StringToHGlobalAnsi(description);
      nDesc = static_cast<const char *>(ptr.ToPointer());
      Runtime::InteropServices::Marshal::FreeHGlobal(ptr);
    }
    return NativeAddTrackingEvent(transactionID, nStatus, nDesc);
  }

  static DataTable ^ GetOrderTracking(int transactionID) {
    DataTable ^ dt = gcnew DataTable();
    dt->Columns->Add("Status", String::typeid);
    dt->Columns->Add("Keterangan", String::typeid);
    dt->Columns->Add("Waktu", String::typeid);

    std::vector<TrackingData> tracking = NativeGetOrderTracking(transactionID);
    for (const auto &t : tracking) {
      DataRow ^ row = dt->NewRow();
      row["Status"] = gcnew String(t.status.c_str());
      row["Keterangan"] = gcnew String(t.description.c_str());
      row["Waktu"] = gcnew String(t.createdAt.c_str());
      dt->Rows->Add(row);
    }
    return dt;
  }
};
