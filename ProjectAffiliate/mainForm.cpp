#include "loginForm.h"
#include "registrationForm.h"
#include "sqlite3.h"

void setupDatabase() {
    sqlite3* db;
    if (sqlite3_open("affiliate.db", &db) == SQLITE_OK) {
        const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT);";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            // Handle error
            sqlite3_free(errMsg);
        }
        sqlite3_close(db);
    }
}

void insertUser(const char* username, const char* password) {
    sqlite3* db;
    if (sqlite3_open("affiliate.db", &db) == SQLITE_OK) {
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
}

void printAllUsers() {
    sqlite3* db;
    if (sqlite3_open("affiliate.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT id, username FROM users;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* username = sqlite3_column_text(stmt, 1);
                printf("ID: %d, Username: %s\n", id, username);
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
}

void updateUserPassword(int userId, const char* newPassword) {
    sqlite3* db;
    if (sqlite3_open("affiliate.db", &db) == SQLITE_OK) {
        const char* sql = "UPDATE users SET password = ? WHERE id = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, newPassword, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, userId);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
}

void deleteUser(int userId) {
    sqlite3* db;
    if (sqlite3_open("affiliate.db", &db) == SQLITE_OK) {
        const char* sql = "DELETE FROM users WHERE id = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, userId);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
}

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	ProjectAffiliate::MyForm form;
	Application::Run(% form);
	return 0;
}
