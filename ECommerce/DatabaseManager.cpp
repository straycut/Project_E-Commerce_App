// DatabaseManager.cpp - SQLite Database Operations
// This file mixes native C++ (SQLite) with managed C++/CLI code

// Native code section - compile without CLR
#pragma managed(push, off)

#include "sqlite3.h"
#include <string>
#include <vector>

// Forward declarations from header
struct sqlite3;
struct sqlite3_stmt;

struct UserData {
  int id;
  std::string username;
  std::string password;
  std::string role;
  int saldo;
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
};

struct IncomeData {
  int id;
  int userID;
  int transactionID;
  int amount;
  std::string type;
  std::string description;
  std::string createdAt;
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

  // Create Users table
  const char *createUsersSQL = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "username TEXT UNIQUE NOT NULL,"
                               "password TEXT NOT NULL,"
                               "role TEXT NOT NULL CHECK(role IN ('Admin', "
                               "'Merchant', 'Customer', 'Courier')),"
                               "saldo INTEGER DEFAULT 0,"
                               "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                               ");";

  if (!ExecuteSQL(createUsersSQL))
    return false;

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
  const char *insertAdminSQL =
      "INSERT OR IGNORE INTO users (username, password, role, saldo) "
      "VALUES ('admin', 'admin123', 'Admin', 0);";

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

  const char *sql = "INSERT INTO users (username, password, role, saldo) "
                    "VALUES (?, ?, ?, 0);";
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

  const char *sql = "SELECT id, username, password, role, saldo FROM users "
                    "WHERE username = ? AND password = ?;";
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

    sqlite3_finalize(stmt);
    return user;
  }

  sqlite3_finalize(stmt);
  return nullptr;
}

#pragma managed(pop)

// ============ Managed Wrapper Implementation ============
// This section uses CLR/managed code

#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

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
                           String ^ % outRole, int % outUserID,
                           int % outSaldo) {
    std::string user = msclr::interop::marshal_as<std::string>(username);
    std::string pass = msclr::interop::marshal_as<std::string>(password);

    UserData *userData = NativeValidateUser(user, pass);

    if (userData != nullptr) {
      outUserID = userData->id;
      outRole = gcnew String(userData->role.c_str());
      outSaldo = userData->saldo;
      delete userData;
      return true;
    }

    return false;
  }
};
