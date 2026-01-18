#pragma once
#include "DatabaseManager.h"

namespace ECommerce {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Admin Dashboard - Manage users, view income, monitor transactions
/// </summary>
public
ref class adminForm : public System::Windows::Forms::Form {
public:
  adminForm(void) { InitializeComponent(); }

protected:
  ~adminForm() {
    if (components) {
      delete components;
    }
  }

  // UI Controls
private:
  System::Windows::Forms::TabControl ^ tabControl;

private:
  System::Windows::Forms::TabPage ^ tabDashboard;

private:
  System::Windows::Forms::TabPage ^ tabUsers;

private:
  System::Windows::Forms::TabPage ^ tabIncome;

private:
  System::Windows::Forms::TabPage ^ tabTransactions;

  // Dashboard controls
private:
  System::Windows::Forms::Label ^ lblTitle;

private:
  System::Windows::Forms::Panel ^ panelStats;

private:
  System::Windows::Forms::Label ^ lblTotalUsers;

private:
  System::Windows::Forms::Label ^ lblTotalMerchants;

private:
  System::Windows::Forms::Label ^ lblTotalCustomers;

private:
  System::Windows::Forms::Label ^ lblTotalCouriers;

private:
  System::Windows::Forms::Label ^ lblTotalTransactions;

private:
  System::Windows::Forms::Label ^ lblTotalIncome;

private:
  System::Windows::Forms::Label ^ lblAppIncome;

private:
  System::Windows::Forms::Label ^ lblMerchantIncome;

private:
  System::Windows::Forms::Label ^ lblCourierIncome;

private:
  System::Windows::Forms::Label ^ lblActiveUsers;

private:
  System::Windows::Forms::Label ^ lblInactiveUsers;

private:
  System::Windows::Forms::Panel ^ panelIncomeBreakdown;

private:
  System::Windows::Forms::Button ^ btnRefreshStats;

  // User management controls
private:
  System::Windows::Forms::DataGridView ^ dgvUsers;

private:
  System::Windows::Forms::Button ^ btnRefreshUsers;

private:
  System::Windows::Forms::Button ^ btnActivateUser;

private:
  System::Windows::Forms::Button ^ btnDeactivateUser;

private:
  System::Windows::Forms::Button ^ btnDeleteUser;

private:
  System::Windows::Forms::Label ^ lblUserManagement;

  // Income controls
private:
  System::Windows::Forms::DataGridView ^ dgvIncome;

private:
  System::Windows::Forms::Button ^ btnRefreshIncome;

private:
  System::Windows::Forms::Label ^ lblIncomeTitle;

private:
  System::Windows::Forms::Label ^ lblTotalIncomeValue;

  // Transaction controls
private:
  System::Windows::Forms::DataGridView ^ dgvTransactions;

private:
  System::Windows::Forms::Button ^ btnRefreshTransactions;

private:
  System::Windows::Forms::Label ^ lblTransactionTitle;

  // Logout
private:
  System::Windows::Forms::Button ^ btnLogout;

private:
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
      this->tabControl = (gcnew System::Windows::Forms::TabControl());
      this->tabDashboard = (gcnew System::Windows::Forms::TabPage());
      this->lblTitle = (gcnew System::Windows::Forms::Label());
      this->lblTotalUsers = (gcnew System::Windows::Forms::Label());
      this->lblTotalMerchants = (gcnew System::Windows::Forms::Label());
      this->lblTotalCustomers = (gcnew System::Windows::Forms::Label());
      this->lblTotalCouriers = (gcnew System::Windows::Forms::Label());
      this->lblTotalTransactions = (gcnew System::Windows::Forms::Label());
      this->panelIncomeBreakdown = (gcnew System::Windows::Forms::Panel());
      this->lblTotalIncome = (gcnew System::Windows::Forms::Label());
      this->lblAppIncome = (gcnew System::Windows::Forms::Label());
      this->lblMerchantIncome = (gcnew System::Windows::Forms::Label());
      this->lblCourierIncome = (gcnew System::Windows::Forms::Label());
      this->lblActiveUsers = (gcnew System::Windows::Forms::Label());
      this->lblInactiveUsers = (gcnew System::Windows::Forms::Label());
      this->btnRefreshStats = (gcnew System::Windows::Forms::Button());
      this->tabUsers = (gcnew System::Windows::Forms::TabPage());
      this->lblUserManagement = (gcnew System::Windows::Forms::Label());
      this->dgvUsers = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshUsers = (gcnew System::Windows::Forms::Button());
      this->btnActivateUser = (gcnew System::Windows::Forms::Button());
      this->btnDeactivateUser = (gcnew System::Windows::Forms::Button());
      this->btnDeleteUser = (gcnew System::Windows::Forms::Button());
      this->tabIncome = (gcnew System::Windows::Forms::TabPage());
      this->lblIncomeTitle = (gcnew System::Windows::Forms::Label());
      this->lblTotalIncomeValue = (gcnew System::Windows::Forms::Label());
      this->dgvIncome = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshIncome = (gcnew System::Windows::Forms::Button());
      this->tabTransactions = (gcnew System::Windows::Forms::TabPage());
      this->lblTransactionTitle = (gcnew System::Windows::Forms::Label());
      this->dgvTransactions = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshTransactions = (gcnew System::Windows::Forms::Button());
      this->panelStats = (gcnew System::Windows::Forms::Panel());
      this->btnLogout = (gcnew System::Windows::Forms::Button());
      this->tabControl->SuspendLayout();
      this->tabDashboard->SuspendLayout();
      this->panelIncomeBreakdown->SuspendLayout();
      this->tabUsers->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsers))->BeginInit();
      this->tabIncome->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvIncome))->BeginInit();
      this->tabTransactions->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvTransactions))->BeginInit();
      this->SuspendLayout();
      // 
      // tabControl
      // 
      this->tabControl->Controls->Add(this->tabDashboard);
      this->tabControl->Controls->Add(this->tabUsers);
      this->tabControl->Controls->Add(this->tabIncome);
      this->tabControl->Controls->Add(this->tabTransactions);
      this->tabControl->Location = System::Drawing::Point(12, 12);
      this->tabControl->Name = L"tabControl";
      this->tabControl->SelectedIndex = 0;
      this->tabControl->Size = System::Drawing::Size(860, 480);
      this->tabControl->TabIndex = 0;
      // 
      // tabDashboard
      // 
      this->tabDashboard->Controls->Add(this->lblTitle);
      this->tabDashboard->Controls->Add(this->lblTotalUsers);
      this->tabDashboard->Controls->Add(this->lblTotalMerchants);
      this->tabDashboard->Controls->Add(this->lblTotalCustomers);
      this->tabDashboard->Controls->Add(this->lblTotalCouriers);
      this->tabDashboard->Controls->Add(this->lblTotalTransactions);
      this->tabDashboard->Controls->Add(this->panelIncomeBreakdown);
      this->tabDashboard->Controls->Add(this->lblActiveUsers);
      this->tabDashboard->Controls->Add(this->lblInactiveUsers);
      this->tabDashboard->Controls->Add(this->btnRefreshStats);
      this->tabDashboard->Location = System::Drawing::Point(4, 22);
      this->tabDashboard->Name = L"tabDashboard";
      this->tabDashboard->Padding = System::Windows::Forms::Padding(3);
      this->tabDashboard->Size = System::Drawing::Size(852, 454);
      this->tabDashboard->TabIndex = 0;
      this->tabDashboard->Text = L"Dashboard";
      this->tabDashboard->UseVisualStyleBackColor = true;
      this->tabDashboard->Click += gcnew System::EventHandler(this, &adminForm::tabDashboard_Click);
      // 
      // lblTitle
      // 
      this->lblTitle->AutoSize = true;
      this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
      this->lblTitle->Location = System::Drawing::Point(20, 20);
      this->lblTitle->Name = L"lblTitle";
      this->lblTitle->Size = System::Drawing::Size(221, 32);
      this->lblTitle->TabIndex = 0;
      this->lblTitle->Text = L"Admin Dashboard";
      // 
      // lblTotalUsers
      // 
      this->lblTotalUsers->AutoSize = true;
      this->lblTotalUsers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblTotalUsers->Location = System::Drawing::Point(30, 80);
      this->lblTotalUsers->Name = L"lblTotalUsers";
      this->lblTotalUsers->Size = System::Drawing::Size(101, 21);
      this->lblTotalUsers->TabIndex = 1;
      this->lblTotalUsers->Text = L"Total Users: 0";
      // 
      // lblTotalMerchants
      // 
      this->lblTotalMerchants->AutoSize = true;
      this->lblTotalMerchants->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblTotalMerchants->Location = System::Drawing::Point(30, 110);
      this->lblTotalMerchants->Name = L"lblTotalMerchants";
      this->lblTotalMerchants->Size = System::Drawing::Size(99, 21);
      this->lblTotalMerchants->TabIndex = 2;
      this->lblTotalMerchants->Text = L"Merchants: 0";
      // 
      // lblTotalCustomers
      // 
      this->lblTotalCustomers->AutoSize = true;
      this->lblTotalCustomers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblTotalCustomers->Location = System::Drawing::Point(30, 140);
      this->lblTotalCustomers->Name = L"lblTotalCustomers";
      this->lblTotalCustomers->Size = System::Drawing::Size(101, 21);
      this->lblTotalCustomers->TabIndex = 3;
      this->lblTotalCustomers->Text = L"Customers: 0";
      // 
      // lblTotalCouriers
      // 
      this->lblTotalCouriers->AutoSize = true;
      this->lblTotalCouriers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblTotalCouriers->Location = System::Drawing::Point(30, 170);
      this->lblTotalCouriers->Name = L"lblTotalCouriers";
      this->lblTotalCouriers->Size = System::Drawing::Size(85, 21);
      this->lblTotalCouriers->TabIndex = 4;
      this->lblTotalCouriers->Text = L"Couriers: 0";
      // 
      // lblTotalTransactions
      // 
      this->lblTotalTransactions->AutoSize = true;
      this->lblTotalTransactions->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblTotalTransactions->Location = System::Drawing::Point(453, 260);
      this->lblTotalTransactions->Name = L"lblTotalTransactions";
      this->lblTotalTransactions->Size = System::Drawing::Size(148, 21);
      this->lblTotalTransactions->TabIndex = 5;
      this->lblTotalTransactions->Text = L"Total Transactions: 0";
      this->lblTotalTransactions->Click += gcnew System::EventHandler(this, &adminForm::lblTotalTransactions_Click);
      // 
      // panelIncomeBreakdown
      // 
      this->panelIncomeBreakdown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
          static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
      this->panelIncomeBreakdown->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panelIncomeBreakdown->Controls->Add(this->lblTotalIncome);
      this->panelIncomeBreakdown->Controls->Add(this->lblAppIncome);
      this->panelIncomeBreakdown->Controls->Add(this->lblMerchantIncome);
      this->panelIncomeBreakdown->Controls->Add(this->lblCourierIncome);
      this->panelIncomeBreakdown->Location = System::Drawing::Point(450, 80);
      this->panelIncomeBreakdown->Name = L"panelIncomeBreakdown";
      this->panelIncomeBreakdown->Size = System::Drawing::Size(380, 150);
      this->panelIncomeBreakdown->TabIndex = 10;
      // 
      // lblTotalIncome
      // 
      this->lblTotalIncome->AutoSize = true;
      this->lblTotalIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblTotalIncome->ForeColor = System::Drawing::Color::DarkGreen;
      this->lblTotalIncome->Location = System::Drawing::Point(15, 10);
      this->lblTotalIncome->Name = L"lblTotalIncome";
      this->lblTotalIncome->Size = System::Drawing::Size(176, 25);
      this->lblTotalIncome->TabIndex = 6;
      this->lblTotalIncome->Text = L"Total Income: Rp 0";
      // 
      // lblAppIncome
      // 
      this->lblAppIncome->AutoSize = true;
      this->lblAppIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->lblAppIncome->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
          static_cast<System::Int32>(static_cast<System::Byte>(204)));
      this->lblAppIncome->Location = System::Drawing::Point(25, 45);
      this->lblAppIncome->Name = L"lblAppIncome";
      this->lblAppIncome->Size = System::Drawing::Size(98, 20);
      this->lblAppIncome->TabIndex = 11;
      this->lblAppIncome->Text = L"Aplikasi: Rp 0";
      this->lblAppIncome->Click += gcnew System::EventHandler(this, &adminForm::lblAppIncome_Click);
      // 
      // lblMerchantIncome
      // 
      this->lblMerchantIncome->AutoSize = true;
      this->lblMerchantIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->lblMerchantIncome->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
          static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
      this->lblMerchantIncome->Location = System::Drawing::Point(25, 75);
      this->lblMerchantIncome->Name = L"lblMerchantIncome";
      this->lblMerchantIncome->Size = System::Drawing::Size(108, 20);
      this->lblMerchantIncome->TabIndex = 12;
      this->lblMerchantIncome->Text = L"Merchant: Rp 0";
      // 
      // lblCourierIncome
      // 
      this->lblCourierIncome->AutoSize = true;
      this->lblCourierIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->lblCourierIncome->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
          static_cast<System::Int32>(static_cast<System::Byte>(152)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
      this->lblCourierIncome->Location = System::Drawing::Point(25, 105);
      this->lblCourierIncome->Name = L"lblCourierIncome";
      this->lblCourierIncome->Size = System::Drawing::Size(94, 20);
      this->lblCourierIncome->TabIndex = 13;
      this->lblCourierIncome->Text = L"Courier: Rp 0";
      // 
      // lblActiveUsers
      // 
      this->lblActiveUsers->AutoSize = true;
      this->lblActiveUsers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblActiveUsers->ForeColor = System::Drawing::Color::Green;
      this->lblActiveUsers->Location = System::Drawing::Point(250, 110);
      this->lblActiveUsers->Name = L"lblActiveUsers";
      this->lblActiveUsers->Size = System::Drawing::Size(111, 21);
      this->lblActiveUsers->TabIndex = 7;
      this->lblActiveUsers->Text = L"Active Users: 0";
      // 
      // lblInactiveUsers
      // 
      this->lblInactiveUsers->AutoSize = true;
      this->lblInactiveUsers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblInactiveUsers->ForeColor = System::Drawing::Color::Red;
      this->lblInactiveUsers->Location = System::Drawing::Point(250, 140);
      this->lblInactiveUsers->Name = L"lblInactiveUsers";
      this->lblInactiveUsers->Size = System::Drawing::Size(122, 21);
      this->lblInactiveUsers->TabIndex = 8;
      this->lblInactiveUsers->Text = L"Inactive Users: 0";
      // 
      // btnRefreshStats
      // 
      this->btnRefreshStats->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
          static_cast<System::Int32>(static_cast<System::Byte>(204)));
      this->btnRefreshStats->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
      this->btnRefreshStats->ForeColor = System::Drawing::Color::White;
      this->btnRefreshStats->Location = System::Drawing::Point(30, 260);
      this->btnRefreshStats->Name = L"btnRefreshStats";
      this->btnRefreshStats->Size = System::Drawing::Size(130, 35);
      this->btnRefreshStats->TabIndex = 9;
      this->btnRefreshStats->Text = L"Refresh Stats";
      this->btnRefreshStats->UseVisualStyleBackColor = false;
      this->btnRefreshStats->Click += gcnew System::EventHandler(this, &adminForm::btnRefreshStats_Click);
      // 
      // tabUsers
      // 
      this->tabUsers->Controls->Add(this->lblUserManagement);
      this->tabUsers->Controls->Add(this->dgvUsers);
      this->tabUsers->Controls->Add(this->btnRefreshUsers);
      this->tabUsers->Controls->Add(this->btnActivateUser);
      this->tabUsers->Controls->Add(this->btnDeactivateUser);
      this->tabUsers->Controls->Add(this->btnDeleteUser);
      this->tabUsers->Location = System::Drawing::Point(4, 22);
      this->tabUsers->Name = L"tabUsers";
      this->tabUsers->Padding = System::Windows::Forms::Padding(3);
      this->tabUsers->Size = System::Drawing::Size(852, 454);
      this->tabUsers->TabIndex = 1;
      this->tabUsers->Text = L"User Management";
      this->tabUsers->UseVisualStyleBackColor = true;
      // 
      // lblUserManagement
      // 
      this->lblUserManagement->AutoSize = true;
      this->lblUserManagement->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblUserManagement->Location = System::Drawing::Point(15, 15);
      this->lblUserManagement->Name = L"lblUserManagement";
      this->lblUserManagement->Size = System::Drawing::Size(175, 25);
      this->lblUserManagement->TabIndex = 0;
      this->lblUserManagement->Text = L"User Management";
      // 
      // dgvUsers
      // 
      this->dgvUsers->AllowUserToAddRows = false;
      this->dgvUsers->AllowUserToDeleteRows = false;
      this->dgvUsers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvUsers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvUsers->Location = System::Drawing::Point(15, 50);
      this->dgvUsers->MultiSelect = false;
      this->dgvUsers->Name = L"dgvUsers";
      this->dgvUsers->ReadOnly = true;
      this->dgvUsers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
      this->dgvUsers->Size = System::Drawing::Size(820, 340);
      this->dgvUsers->TabIndex = 0;
      // 
      // btnRefreshUsers
      // 
      this->btnRefreshUsers->Location = System::Drawing::Point(15, 400);
      this->btnRefreshUsers->Name = L"btnRefreshUsers";
      this->btnRefreshUsers->Size = System::Drawing::Size(100, 30);
      this->btnRefreshUsers->TabIndex = 1;
      this->btnRefreshUsers->Text = L"Refresh";
      this->btnRefreshUsers->Click += gcnew System::EventHandler(this, &adminForm::btnRefreshUsers_Click);
      // 
      // btnActivateUser
      // 
      this->btnActivateUser->BackColor = System::Drawing::Color::LightGreen;
      this->btnActivateUser->Location = System::Drawing::Point(130, 400);
      this->btnActivateUser->Name = L"btnActivateUser";
      this->btnActivateUser->Size = System::Drawing::Size(120, 30);
      this->btnActivateUser->TabIndex = 2;
      this->btnActivateUser->Text = L"Activate User";
      this->btnActivateUser->UseVisualStyleBackColor = false;
      this->btnActivateUser->Click += gcnew System::EventHandler(this, &adminForm::btnActivateUser_Click);
      // 
      // btnDeactivateUser
      // 
      this->btnDeactivateUser->BackColor = System::Drawing::Color::LightCoral;
      this->btnDeactivateUser->Location = System::Drawing::Point(260, 400);
      this->btnDeactivateUser->Name = L"btnDeactivateUser";
      this->btnDeactivateUser->Size = System::Drawing::Size(120, 30);
      this->btnDeactivateUser->TabIndex = 3;
      this->btnDeactivateUser->Text = L"Deactivate User";
      this->btnDeactivateUser->UseVisualStyleBackColor = false;
      this->btnDeactivateUser->Click += gcnew System::EventHandler(this, &adminForm::btnDeactivateUser_Click);
      // 
      // btnDeleteUser
      // 
      this->btnDeleteUser->BackColor = System::Drawing::Color::IndianRed;
      this->btnDeleteUser->ForeColor = System::Drawing::Color::White;
      this->btnDeleteUser->Location = System::Drawing::Point(390, 400);
      this->btnDeleteUser->Name = L"btnDeleteUser";
      this->btnDeleteUser->Size = System::Drawing::Size(100, 30);
      this->btnDeleteUser->TabIndex = 4;
      this->btnDeleteUser->Text = L"Delete User";
      this->btnDeleteUser->UseVisualStyleBackColor = false;
      this->btnDeleteUser->Click += gcnew System::EventHandler(this, &adminForm::btnDeleteUser_Click);
      // 
      // tabIncome
      // 
      this->tabIncome->Controls->Add(this->lblIncomeTitle);
      this->tabIncome->Controls->Add(this->lblTotalIncomeValue);
      this->tabIncome->Controls->Add(this->dgvIncome);
      this->tabIncome->Controls->Add(this->btnRefreshIncome);
      this->tabIncome->Location = System::Drawing::Point(4, 22);
      this->tabIncome->Name = L"tabIncome";
      this->tabIncome->Padding = System::Windows::Forms::Padding(3);
      this->tabIncome->Size = System::Drawing::Size(852, 454);
      this->tabIncome->TabIndex = 2;
      this->tabIncome->Text = L"Income";
      this->tabIncome->UseVisualStyleBackColor = true;
      // 
      // lblIncomeTitle
      // 
      this->lblIncomeTitle->AutoSize = true;
      this->lblIncomeTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblIncomeTitle->Location = System::Drawing::Point(15, 15);
      this->lblIncomeTitle->Name = L"lblIncomeTitle";
      this->lblIncomeTitle->Size = System::Drawing::Size(154, 25);
      this->lblIncomeTitle->TabIndex = 0;
      this->lblIncomeTitle->Text = L"Income Records";
      // 
      // lblTotalIncomeValue
      // 
      this->lblTotalIncomeValue->AutoSize = true;
      this->lblTotalIncomeValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
      this->lblTotalIncomeValue->ForeColor = System::Drawing::Color::DarkGreen;
      this->lblTotalIncomeValue->Location = System::Drawing::Point(600, 15);
      this->lblTotalIncomeValue->Name = L"lblTotalIncomeValue";
      this->lblTotalIncomeValue->Size = System::Drawing::Size(89, 21);
      this->lblTotalIncomeValue->TabIndex = 1;
      this->lblTotalIncomeValue->Text = L"Total: Rp 0";
      // 
      // dgvIncome
      // 
      this->dgvIncome->AllowUserToAddRows = false;
      this->dgvIncome->AllowUserToDeleteRows = false;
      this->dgvIncome->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvIncome->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvIncome->Location = System::Drawing::Point(15, 50);
      this->dgvIncome->MultiSelect = false;
      this->dgvIncome->Name = L"dgvIncome";
      this->dgvIncome->ReadOnly = true;
      this->dgvIncome->Size = System::Drawing::Size(820, 340);
      this->dgvIncome->TabIndex = 0;
      // 
      // btnRefreshIncome
      // 
      this->btnRefreshIncome->Location = System::Drawing::Point(15, 400);
      this->btnRefreshIncome->Name = L"btnRefreshIncome";
      this->btnRefreshIncome->Size = System::Drawing::Size(100, 30);
      this->btnRefreshIncome->TabIndex = 2;
      this->btnRefreshIncome->Text = L"Refresh";
      this->btnRefreshIncome->Click += gcnew System::EventHandler(this, &adminForm::btnRefreshIncome_Click);
      // 
      // tabTransactions
      // 
      this->tabTransactions->Controls->Add(this->lblTransactionTitle);
      this->tabTransactions->Controls->Add(this->dgvTransactions);
      this->tabTransactions->Controls->Add(this->btnRefreshTransactions);
      this->tabTransactions->Location = System::Drawing::Point(4, 22);
      this->tabTransactions->Name = L"tabTransactions";
      this->tabTransactions->Padding = System::Windows::Forms::Padding(3);
      this->tabTransactions->Size = System::Drawing::Size(852, 454);
      this->tabTransactions->TabIndex = 3;
      this->tabTransactions->Text = L"Transactions";
      this->tabTransactions->UseVisualStyleBackColor = true;
      // 
      // lblTransactionTitle
      // 
      this->lblTransactionTitle->AutoSize = true;
      this->lblTransactionTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblTransactionTitle->Location = System::Drawing::Point(15, 15);
      this->lblTransactionTitle->Name = L"lblTransactionTitle";
      this->lblTransactionTitle->Size = System::Drawing::Size(186, 25);
      this->lblTransactionTitle->TabIndex = 0;
      this->lblTransactionTitle->Text = L"Transaction History";
      // 
      // dgvTransactions
      // 
      this->dgvTransactions->AllowUserToAddRows = false;
      this->dgvTransactions->AllowUserToDeleteRows = false;
      this->dgvTransactions->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvTransactions->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvTransactions->Location = System::Drawing::Point(15, 50);
      this->dgvTransactions->MultiSelect = false;
      this->dgvTransactions->Name = L"dgvTransactions";
      this->dgvTransactions->ReadOnly = true;
      this->dgvTransactions->Size = System::Drawing::Size(820, 340);
      this->dgvTransactions->TabIndex = 0;
      // 
      // btnRefreshTransactions
      // 
      this->btnRefreshTransactions->Location = System::Drawing::Point(15, 400);
      this->btnRefreshTransactions->Name = L"btnRefreshTransactions";
      this->btnRefreshTransactions->Size = System::Drawing::Size(100, 30);
      this->btnRefreshTransactions->TabIndex = 1;
      this->btnRefreshTransactions->Text = L"Refresh";
      this->btnRefreshTransactions->Click += gcnew System::EventHandler(this, &adminForm::btnRefreshTransactions_Click);
      // 
      // panelStats
      // 
      this->panelStats->Location = System::Drawing::Point(0, 0);
      this->panelStats->Name = L"panelStats";
      this->panelStats->Size = System::Drawing::Size(200, 100);
      this->panelStats->TabIndex = 0;
      // 
      // btnLogout
      // 
      this->btnLogout->BackColor = System::Drawing::Color::LightGray;
      this->btnLogout->Location = System::Drawing::Point(780, 500);
      this->btnLogout->Name = L"btnLogout";
      this->btnLogout->Size = System::Drawing::Size(90, 30);
      this->btnLogout->TabIndex = 1;
      this->btnLogout->Text = L"Logout";
      this->btnLogout->UseVisualStyleBackColor = false;
      this->btnLogout->Click += gcnew System::EventHandler(this, &adminForm::btnLogout_Click);
      // 
      // adminForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(884, 541);
      this->Controls->Add(this->tabControl);
      this->Controls->Add(this->btnLogout);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->MaximizeBox = false;
      this->Name = L"adminForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Admin Dashboard - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &adminForm::adminForm_Load);
      this->tabControl->ResumeLayout(false);
      this->tabDashboard->ResumeLayout(false);
      this->tabDashboard->PerformLayout();
      this->panelIncomeBreakdown->ResumeLayout(false);
      this->panelIncomeBreakdown->PerformLayout();
      this->tabUsers->ResumeLayout(false);
      this->tabUsers->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsers))->EndInit();
      this->tabIncome->ResumeLayout(false);
      this->tabIncome->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvIncome))->EndInit();
      this->tabTransactions->ResumeLayout(false);
      this->tabTransactions->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvTransactions))->EndInit();
      this->ResumeLayout(false);

  }
#pragma endregion

  // ========== Event Handlers (implementations in adminForm.cpp) ==========
private:
  System::Void adminForm_Load(System::Object ^ sender, System::EventArgs ^ e);
  void LoadDashboardStats();
  void LoadUsers();
  void LoadIncome();
  void LoadTransactions();
  System::Void btnRefreshStats_Click(System::Object ^ sender,
                                     System::EventArgs ^ e);
  System::Void btnRefreshUsers_Click(System::Object ^ sender,
                                     System::EventArgs ^ e);
  System::Void btnActivateUser_Click(System::Object ^ sender,
                                     System::EventArgs ^ e);
  System::Void btnDeactivateUser_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnDeleteUser_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void btnRefreshIncome_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  System::Void btnRefreshTransactions_Click(System::Object ^ sender,
                                            System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void tabDashboard_Click(System::Object ^ sender,
                                  System::EventArgs ^ e);
private: System::Void lblTotalTransactions_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lblAppIncome_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
} // namespace ECommerce
