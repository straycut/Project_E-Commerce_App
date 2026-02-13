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
public:
  adminForm(int userID) {
    InitializeComponent();
    currentUserID = userID;
  }
  adminForm(void) {
    InitializeComponent();
    currentUserID = 0;
  }

protected:
  ~adminForm() {
    if (components) {
      delete components;
    }
  }

private:
  int currentUserID;

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

private:
  System::Windows::Forms::TextBox ^ txtSearchUser;

private:
  System::Windows::Forms::ComboBox ^ cmbFilterRole;

private:
  System::Windows::Forms::Label ^ lblSearch;

private:
  System::Windows::Forms::Label ^ lblFilterRole;

private:
  System::Windows::Forms::Button ^ btnAddUser;

private:
  System::Windows::Forms::Panel ^ panelAddUser;

private:
  System::Windows::Forms::Label ^ lblNewUsername;

private:
  System::Windows::Forms::TextBox ^ txtNewUsername;

private:
  System::Windows::Forms::Label ^ lblNewPassword;

private:
  System::Windows::Forms::TextBox ^ txtNewPassword;

private:
  System::Windows::Forms::Label ^ lblNewRole;

private:
  System::Windows::Forms::ComboBox ^ cmbNewRole;

private:
  System::Windows::Forms::Button ^ btnSaveUser;

private:
  System::Windows::Forms::Button ^ btnCancelAddUser;

  // Income controls
private:
  System::Windows::Forms::Label ^ lblAdminWithdrawLabel;

private:
  System::Windows::Forms::TextBox ^ txtAdminWithdrawAmount;

private:
  System::Windows::Forms::Button ^ btnAdminWithdraw;

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

private:
  System::Windows::Forms::Button ^ btnEditTransactionStatus;

private:
  System::Windows::Forms::Button ^ btnDeleteTransaction;

private:
  System::Windows::Forms::Label ^ lblFilterStatus;

private:
  System::Windows::Forms::ComboBox ^ cmbFilterStatus;

  // Products controls
private:
  System::Windows::Forms::TabPage ^ tabProducts;

private:
  System::Windows::Forms::DataGridView ^ dgvProducts;

private:
  System::Windows::Forms::Button ^ btnRefreshProducts;

private:
  System::Windows::Forms::Button ^ btnEditProduct;

private:
  System::Windows::Forms::Button ^ btnDeleteProduct;

private:
  System::Windows::Forms::Label ^ lblProductsTitle;

private:
  System::Windows::Forms::Panel ^ panelEditProduct;

private:
  System::Windows::Forms::Label ^ lblEditProductName;

private:
  System::Windows::Forms::TextBox ^ txtEditProductName;

private:
  System::Windows::Forms::Label ^ lblEditProductPrice;

private:
  System::Windows::Forms::TextBox ^ txtEditProductPrice;

private:
  System::Windows::Forms::Label ^ lblEditProductStock;

private:
  System::Windows::Forms::TextBox ^ txtEditProductStock;

private:
  System::Windows::Forms::Button ^ btnSaveProduct;

private:
  System::Windows::Forms::Button ^ btnCancelEditProduct;

private:
  System::Windows::Forms::Label ^ lblEditProductKategori;

private:
  System::Windows::Forms::TextBox ^ txtEditProductKategori;

private:
  System::Windows::Forms::Label ^ lblEditProductDeskripsi;

private:
  System::Windows::Forms::TextBox ^ txtEditProductDeskripsi;

private:
  int editProductID;

  // Logout
private:
  System::Windows::Forms::Button ^ btnLogout;

private:
private:
  System::Windows::Forms::Label ^ label1;

private:
  System::Windows::Forms::ContextMenuStrip ^ contextMenuStrip1;

private:
  System::ComponentModel::IContainer ^ components;

private:
private:
#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
    this->components = (gcnew System::ComponentModel::Container());
    this->tabControl = (gcnew System::Windows::Forms::TabControl());
    this->tabDashboard = (gcnew System::Windows::Forms::TabPage());
    this->lblTotalIncome = (gcnew System::Windows::Forms::Label());
    this->lblAppIncome = (gcnew System::Windows::Forms::Label());
    this->lblMerchantIncome = (gcnew System::Windows::Forms::Label());
    this->lblCourierIncome = (gcnew System::Windows::Forms::Label());
    this->lblTotalMerchants = (gcnew System::Windows::Forms::Label());
    this->lblTotalCouriers = (gcnew System::Windows::Forms::Label());
    this->lblTotalUsers = (gcnew System::Windows::Forms::Label());
    this->lblTotalCustomers = (gcnew System::Windows::Forms::Label());
    this->lblActiveUsers = (gcnew System::Windows::Forms::Label());
    this->lblInactiveUsers = (gcnew System::Windows::Forms::Label());
    this->lblTotalTransactions = (gcnew System::Windows::Forms::Label());
    this->btnRefreshStats = (gcnew System::Windows::Forms::Button());
    this->lblTitle = (gcnew System::Windows::Forms::Label());
    this->btnAdminWithdraw = (gcnew System::Windows::Forms::Button());
    this->lblAdminWithdrawLabel = (gcnew System::Windows::Forms::Label());
    this->txtAdminWithdrawAmount = (gcnew System::Windows::Forms::TextBox());
    this->tabUsers = (gcnew System::Windows::Forms::TabPage());
    this->lblUserManagement = (gcnew System::Windows::Forms::Label());
    this->dgvUsers = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshUsers = (gcnew System::Windows::Forms::Button());
    this->btnActivateUser = (gcnew System::Windows::Forms::Button());
    this->btnDeactivateUser = (gcnew System::Windows::Forms::Button());
    this->btnDeleteUser = (gcnew System::Windows::Forms::Button());
    this->lblSearch = (gcnew System::Windows::Forms::Label());
    this->txtSearchUser = (gcnew System::Windows::Forms::TextBox());
    this->lblFilterRole = (gcnew System::Windows::Forms::Label());
    this->cmbFilterRole = (gcnew System::Windows::Forms::ComboBox());
    this->btnAddUser = (gcnew System::Windows::Forms::Button());
    this->panelAddUser = (gcnew System::Windows::Forms::Panel());
    this->lblNewUsername = (gcnew System::Windows::Forms::Label());
    this->txtNewUsername = (gcnew System::Windows::Forms::TextBox());
    this->lblNewPassword = (gcnew System::Windows::Forms::Label());
    this->txtNewPassword = (gcnew System::Windows::Forms::TextBox());
    this->lblNewRole = (gcnew System::Windows::Forms::Label());
    this->cmbNewRole = (gcnew System::Windows::Forms::ComboBox());
    this->btnSaveUser = (gcnew System::Windows::Forms::Button());
    this->btnCancelAddUser = (gcnew System::Windows::Forms::Button());
    this->tabIncome = (gcnew System::Windows::Forms::TabPage());
    this->lblIncomeTitle = (gcnew System::Windows::Forms::Label());
    this->lblTotalIncomeValue = (gcnew System::Windows::Forms::Label());
    this->dgvIncome = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshIncome = (gcnew System::Windows::Forms::Button());
    this->tabTransactions = (gcnew System::Windows::Forms::TabPage());
    this->lblTransactionTitle = (gcnew System::Windows::Forms::Label());
    this->dgvTransactions = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshTransactions = (gcnew System::Windows::Forms::Button());
    this->lblFilterStatus = (gcnew System::Windows::Forms::Label());
    this->cmbFilterStatus = (gcnew System::Windows::Forms::ComboBox());
    this->btnEditTransactionStatus = (gcnew System::Windows::Forms::Button());
    this->btnDeleteTransaction = (gcnew System::Windows::Forms::Button());
    this->tabProducts = (gcnew System::Windows::Forms::TabPage());
    this->lblProductsTitle = (gcnew System::Windows::Forms::Label());
    this->dgvProducts = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshProducts = (gcnew System::Windows::Forms::Button());
    this->btnEditProduct = (gcnew System::Windows::Forms::Button());
    this->btnDeleteProduct = (gcnew System::Windows::Forms::Button());
    this->panelEditProduct = (gcnew System::Windows::Forms::Panel());
    this->lblEditProductName = (gcnew System::Windows::Forms::Label());
    this->txtEditProductName = (gcnew System::Windows::Forms::TextBox());
    this->lblEditProductPrice = (gcnew System::Windows::Forms::Label());
    this->txtEditProductPrice = (gcnew System::Windows::Forms::TextBox());
    this->lblEditProductStock = (gcnew System::Windows::Forms::Label());
    this->txtEditProductStock = (gcnew System::Windows::Forms::TextBox());
    this->btnSaveProduct = (gcnew System::Windows::Forms::Button());
    this->btnCancelEditProduct = (gcnew System::Windows::Forms::Button());
    this->lblEditProductKategori = (gcnew System::Windows::Forms::Label());
    this->txtEditProductKategori = (gcnew System::Windows::Forms::TextBox());
    this->lblEditProductDeskripsi = (gcnew System::Windows::Forms::Label());
    this->txtEditProductDeskripsi = (gcnew System::Windows::Forms::TextBox());
    this->panelStats = (gcnew System::Windows::Forms::Panel());
    this->btnLogout = (gcnew System::Windows::Forms::Button());
    this->contextMenuStrip1 =
        (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->tabControl->SuspendLayout();
    this->tabDashboard->SuspendLayout();
    this->tabUsers->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvUsers))
        ->BeginInit();
    this->panelAddUser->SuspendLayout();
    this->tabIncome->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvIncome))
        ->BeginInit();
    this->tabTransactions->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvTransactions))
        ->BeginInit();
    this->tabProducts->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvProducts))
        ->BeginInit();
    this->panelEditProduct->SuspendLayout();
    this->SuspendLayout();
    //
    // tabControl
    //
    this->tabControl->Controls->Add(this->tabDashboard);
    this->tabControl->Controls->Add(this->tabUsers);
    this->tabControl->Controls->Add(this->tabIncome);
    this->tabControl->Controls->Add(this->tabTransactions);
    this->tabControl->Controls->Add(this->tabProducts);
    this->tabControl->Location = System::Drawing::Point(12, 12);
    this->tabControl->Name = L"tabControl";
    this->tabControl->SelectedIndex = 0;
    this->tabControl->Size = System::Drawing::Size(860, 481);
    this->tabControl->TabIndex = 0;
    //
    // tabDashboard
    //
    this->tabDashboard->Controls->Add(this->label1);
    this->tabDashboard->Controls->Add(this->lblTotalMerchants);
    this->tabDashboard->Controls->Add(this->btnAdminWithdraw);
    this->tabDashboard->Controls->Add(this->txtAdminWithdrawAmount);
    this->tabDashboard->Controls->Add(this->lblTotalIncome);
    this->tabDashboard->Controls->Add(this->lblAdminWithdrawLabel);
    this->tabDashboard->Controls->Add(this->lblTotalCouriers);
    this->tabDashboard->Controls->Add(this->lblAppIncome);
    this->tabDashboard->Controls->Add(this->lblTotalUsers);
    this->tabDashboard->Controls->Add(this->lblTotalCustomers);
    this->tabDashboard->Controls->Add(this->lblActiveUsers);
    this->tabDashboard->Controls->Add(this->lblInactiveUsers);
    this->tabDashboard->Controls->Add(this->lblTotalTransactions);
    this->tabDashboard->Controls->Add(this->btnRefreshStats);
    this->tabDashboard->Controls->Add(this->lblTitle);
    this->tabDashboard->Controls->Add(this->lblMerchantIncome);
    this->tabDashboard->Controls->Add(this->lblCourierIncome);
    this->tabDashboard->Location = System::Drawing::Point(4, 22);
    this->tabDashboard->Name = L"tabDashboard";
    this->tabDashboard->Padding = System::Windows::Forms::Padding(3);
    this->tabDashboard->Size = System::Drawing::Size(852, 455);
    this->tabDashboard->TabIndex = 0;
    this->tabDashboard->Text = L"Dashboard";
    this->tabDashboard->UseVisualStyleBackColor = true;
    this->tabDashboard->Click +=
        gcnew System::EventHandler(this, &adminForm::tabDashboard_Click);
    //
    // lblTotalIncome
    //
    this->lblTotalIncome->AutoSize = true;
    this->lblTotalIncome->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblTotalIncome->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblTotalIncome->Location = System::Drawing::Point(16, 92);
    this->lblTotalIncome->Name = L"lblTotalIncome";
    this->lblTotalIncome->Size = System::Drawing::Size(176, 25);
    this->lblTotalIncome->TabIndex = 6;
    this->lblTotalIncome->Text = L"Total Income: Rp 0";
    //
    // lblAppIncome
    //
    this->lblAppIncome->AutoSize = true;
    this->lblAppIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
    this->lblAppIncome->ForeColor = System::Drawing::SystemColors::ControlText;
    this->lblAppIncome->Location = System::Drawing::Point(17, 123);
    this->lblAppIncome->Name = L"lblAppIncome";
    this->lblAppIncome->Size = System::Drawing::Size(98, 20);
    this->lblAppIncome->TabIndex = 11;
    this->lblAppIncome->Text = L"Aplikasi: Rp 0";
    this->lblAppIncome->Click +=
        gcnew System::EventHandler(this, &adminForm::lblAppIncome_Click);
    //
    // lblMerchantIncome
    //
    this->lblMerchantIncome->AutoSize = true;
    this->lblMerchantIncome->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 11));
    this->lblMerchantIncome->ForeColor =
        System::Drawing::SystemColors::ControlText;
    this->lblMerchantIncome->Location = System::Drawing::Point(17, 146);
    this->lblMerchantIncome->Name = L"lblMerchantIncome";
    this->lblMerchantIncome->Size = System::Drawing::Size(108, 20);
    this->lblMerchantIncome->TabIndex = 12;
    this->lblMerchantIncome->Text = L"Merchant: Rp 0";
    //
    // lblCourierIncome
    //
    this->lblCourierIncome->AutoSize = true;
    this->lblCourierIncome->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 11));
    this->lblCourierIncome->ForeColor =
        System::Drawing::SystemColors::ControlText;
    this->lblCourierIncome->Location = System::Drawing::Point(17, 169);
    this->lblCourierIncome->Name = L"lblCourierIncome";
    this->lblCourierIncome->Size = System::Drawing::Size(94, 20);
    this->lblCourierIncome->TabIndex = 13;
    this->lblCourierIncome->Text = L"Courier: Rp 0";
    //
    // lblTotalMerchants
    //
    this->lblTotalMerchants->AutoSize = true;
    this->lblTotalMerchants->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 12));
    this->lblTotalMerchants->Location = System::Drawing::Point(17, 259);
    this->lblTotalMerchants->Name = L"lblTotalMerchants";
    this->lblTotalMerchants->Size = System::Drawing::Size(99, 21);
    this->lblTotalMerchants->TabIndex = 2;
    this->lblTotalMerchants->Text = L"Merchants: 0";
    //
    // lblTotalCouriers
    //
    this->lblTotalCouriers->AutoSize = true;
    this->lblTotalCouriers->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 12));
    this->lblTotalCouriers->Location = System::Drawing::Point(17, 306);
    this->lblTotalCouriers->Name = L"lblTotalCouriers";
    this->lblTotalCouriers->Size = System::Drawing::Size(85, 21);
    this->lblTotalCouriers->TabIndex = 4;
    this->lblTotalCouriers->Text = L"Couriers: 0";
    //
    // lblTotalUsers
    //
    this->lblTotalUsers->AutoSize = true;
    this->lblTotalUsers->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->lblTotalUsers->ForeColor = System::Drawing::Color::MediumSeaGreen;
    this->lblTotalUsers->Location = System::Drawing::Point(17, 234);
    this->lblTotalUsers->Name = L"lblTotalUsers";
    this->lblTotalUsers->Size = System::Drawing::Size(110, 21);
    this->lblTotalUsers->TabIndex = 1;
    this->lblTotalUsers->Text = L"Total Users: 0";
    //
    // lblTotalCustomers
    //
    this->lblTotalCustomers->AutoSize = true;
    this->lblTotalCustomers->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 12));
    this->lblTotalCustomers->Location = System::Drawing::Point(17, 283);
    this->lblTotalCustomers->Name = L"lblTotalCustomers";
    this->lblTotalCustomers->Size = System::Drawing::Size(101, 21);
    this->lblTotalCustomers->TabIndex = 3;
    this->lblTotalCustomers->Text = L"Customers: 0";
    //
    // lblActiveUsers
    //
    this->lblActiveUsers->AutoSize = true;
    this->lblActiveUsers->Font = (gcnew System::Drawing::Font(
        L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->lblActiveUsers->ForeColor = System::Drawing::Color::Green;
    this->lblActiveUsers->Location = System::Drawing::Point(17, 327);
    this->lblActiveUsers->Name = L"lblActiveUsers";
    this->lblActiveUsers->Size = System::Drawing::Size(117, 21);
    this->lblActiveUsers->TabIndex = 7;
    this->lblActiveUsers->Text = L"Active Users: 0";
    //
    // lblInactiveUsers
    //
    this->lblInactiveUsers->AutoSize = true;
    this->lblInactiveUsers->Font = (gcnew System::Drawing::Font(
        L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->lblInactiveUsers->ForeColor = System::Drawing::Color::Red;
    this->lblInactiveUsers->Location = System::Drawing::Point(17, 348);
    this->lblInactiveUsers->Name = L"lblInactiveUsers";
    this->lblInactiveUsers->Size = System::Drawing::Size(128, 21);
    this->lblInactiveUsers->TabIndex = 8;
    this->lblInactiveUsers->Text = L"Inactive Users: 0";
    //
    // lblTotalTransactions
    //
    this->lblTotalTransactions->AutoSize = true;
    this->lblTotalTransactions->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 12));
    this->lblTotalTransactions->Location = System::Drawing::Point(17, 189);
    this->lblTotalTransactions->Name = L"lblTotalTransactions";
    this->lblTotalTransactions->Size = System::Drawing::Size(148, 21);
    this->lblTotalTransactions->TabIndex = 5;
    this->lblTotalTransactions->Text = L"Total Transactions: 0";
    this->lblTotalTransactions->Click += gcnew System::EventHandler(
        this, &adminForm::lblTotalTransactions_Click);
    //
    // btnRefreshStats
    //
    this->btnRefreshStats->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnRefreshStats->ForeColor = System::Drawing::Color::White;
    this->btnRefreshStats->Location = System::Drawing::Point(21, 397);
    this->btnRefreshStats->Name = L"btnRefreshStats";
    this->btnRefreshStats->Size = System::Drawing::Size(98, 36);
    this->btnRefreshStats->TabIndex = 9;
    this->btnRefreshStats->Text = L"Refresh Stats";
    this->btnRefreshStats->UseVisualStyleBackColor = false;
    this->btnRefreshStats->Click +=
        gcnew System::EventHandler(this, &adminForm::btnRefreshStats_Click);
    //
    // lblTitle
    //
    this->lblTitle->AutoSize = true;
    this->lblTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
    this->lblTitle->ForeColor = System::Drawing::Color::MediumSeaGreen;
    this->lblTitle->Location = System::Drawing::Point(15, 30);
    this->lblTitle->Name = L"lblTitle";
    this->lblTitle->Size = System::Drawing::Size(221, 32);
    this->lblTitle->TabIndex = 0;
    this->lblTitle->Text = L"Admin Dashboard";
    //
    // btnAdminWithdraw
    //
    this->btnAdminWithdraw->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnAdminWithdraw->ForeColor = System::Drawing::Color::White;
    this->btnAdminWithdraw->Location = System::Drawing::Point(531, 180);
    this->btnAdminWithdraw->Name = L"btnAdminWithdraw";
    this->btnAdminWithdraw->Size = System::Drawing::Size(280, 39);
    this->btnAdminWithdraw->TabIndex = 16;
    this->btnAdminWithdraw->Text = L"Tarik";
    this->btnAdminWithdraw->UseVisualStyleBackColor = false;
    this->btnAdminWithdraw->Click +=
        gcnew System::EventHandler(this, &adminForm::btnAdminWithdraw_Click);
    //
    // lblAdminWithdrawLabel
    //
    this->lblAdminWithdrawLabel->AutoSize = true;
    this->lblAdminWithdrawLabel->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->lblAdminWithdrawLabel->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblAdminWithdrawLabel->Location = System::Drawing::Point(527, 96);
    this->lblAdminWithdrawLabel->Name = L"lblAdminWithdrawLabel";
    this->lblAdminWithdrawLabel->Size = System::Drawing::Size(98, 21);
    this->lblAdminWithdrawLabel->TabIndex = 14;
    this->lblAdminWithdrawLabel->Text = L"Tarik Saldo:";
    //
    // txtAdminWithdrawAmount
    //
    this->txtAdminWithdrawAmount->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->txtAdminWithdrawAmount->Location = System::Drawing::Point(531, 147);
    this->txtAdminWithdrawAmount->Name = L"txtAdminWithdrawAmount";
    this->txtAdminWithdrawAmount->Size = System::Drawing::Size(280, 27);
    this->txtAdminWithdrawAmount->TabIndex = 15;
    //
    // tabUsers
    //
    this->tabUsers->Controls->Add(this->lblUserManagement);
    this->tabUsers->Controls->Add(this->dgvUsers);
    this->tabUsers->Controls->Add(this->btnRefreshUsers);
    this->tabUsers->Controls->Add(this->btnActivateUser);
    this->tabUsers->Controls->Add(this->btnDeactivateUser);
    this->tabUsers->Controls->Add(this->btnDeleteUser);
    this->tabUsers->Controls->Add(this->lblSearch);
    this->tabUsers->Controls->Add(this->txtSearchUser);
    this->tabUsers->Controls->Add(this->lblFilterRole);
    this->tabUsers->Controls->Add(this->cmbFilterRole);
    this->tabUsers->Controls->Add(this->btnAddUser);
    this->tabUsers->Controls->Add(this->panelAddUser);
    this->tabUsers->Location = System::Drawing::Point(4, 22);
    this->tabUsers->Name = L"tabUsers";
    this->tabUsers->Padding = System::Windows::Forms::Padding(3);
    this->tabUsers->Size = System::Drawing::Size(852, 455);
    this->tabUsers->TabIndex = 1;
    this->tabUsers->Text = L"User Management";
    this->tabUsers->UseVisualStyleBackColor = true;
    //
    // lblUserManagement
    //
    this->lblUserManagement->AutoSize = true;
    this->lblUserManagement->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
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
    this->dgvUsers->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvUsers->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvUsers->Location = System::Drawing::Point(15, 75);
    this->dgvUsers->MultiSelect = false;
    this->dgvUsers->Name = L"dgvUsers";
    this->dgvUsers->ReadOnly = true;
    this->dgvUsers->SelectionMode =
        System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->dgvUsers->Size = System::Drawing::Size(820, 315);
    this->dgvUsers->TabIndex = 0;
    //
    // btnRefreshUsers
    //
    this->btnRefreshUsers->Location = System::Drawing::Point(15, 408);
    this->btnRefreshUsers->Name = L"btnRefreshUsers";
    this->btnRefreshUsers->Size = System::Drawing::Size(100, 30);
    this->btnRefreshUsers->TabIndex = 1;
    this->btnRefreshUsers->Text = L"Refresh";
    this->btnRefreshUsers->Click +=
        gcnew System::EventHandler(this, &adminForm::btnRefreshUsers_Click);
    //
    // btnActivateUser
    //
    this->btnActivateUser->BackColor = System::Drawing::Color::White;
    this->btnActivateUser->Location = System::Drawing::Point(130, 408);
    this->btnActivateUser->Name = L"btnActivateUser";
    this->btnActivateUser->Size = System::Drawing::Size(120, 30);
    this->btnActivateUser->TabIndex = 2;
    this->btnActivateUser->Text = L"User Aktif";
    this->btnActivateUser->UseVisualStyleBackColor = false;
    this->btnActivateUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnActivateUser_Click);
    //
    // btnDeactivateUser
    //
    this->btnDeactivateUser->BackColor = System::Drawing::Color::White;
    this->btnDeactivateUser->Location = System::Drawing::Point(260, 408);
    this->btnDeactivateUser->Name = L"btnDeactivateUser";
    this->btnDeactivateUser->Size = System::Drawing::Size(120, 30);
    this->btnDeactivateUser->TabIndex = 3;
    this->btnDeactivateUser->Text = L"Nonaktifkan User";
    this->btnDeactivateUser->UseVisualStyleBackColor = false;
    this->btnDeactivateUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnDeactivateUser_Click);
    //
    // btnDeleteUser
    //
    this->btnDeleteUser->BackColor = System::Drawing::Color::White;
    this->btnDeleteUser->ForeColor = System::Drawing::Color::Black;
    this->btnDeleteUser->Location = System::Drawing::Point(390, 408);
    this->btnDeleteUser->Name = L"btnDeleteUser";
    this->btnDeleteUser->Size = System::Drawing::Size(100, 30);
    this->btnDeleteUser->TabIndex = 4;
    this->btnDeleteUser->Text = L"Hapus User";
    this->btnDeleteUser->UseVisualStyleBackColor = false;
    this->btnDeleteUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnDeleteUser_Click);
    //
    // lblSearch
    //
    this->lblSearch->AutoSize = true;
    this->lblSearch->Location = System::Drawing::Point(15, 50);
    this->lblSearch->Name = L"lblSearch";
    this->lblSearch->Size = System::Drawing::Size(44, 13);
    this->lblSearch->TabIndex = 5;
    this->lblSearch->Text = L"Search:";
    //
    // txtSearchUser
    //
    this->txtSearchUser->Location = System::Drawing::Point(65, 47);
    this->txtSearchUser->Name = L"txtSearchUser";
    this->txtSearchUser->Size = System::Drawing::Size(180, 20);
    this->txtSearchUser->TabIndex = 6;
    this->txtSearchUser->TextChanged +=
        gcnew System::EventHandler(this, &adminForm::txtSearchUser_TextChanged);
    //
    // lblFilterRole
    //
    this->lblFilterRole->AutoSize = true;
    this->lblFilterRole->Location = System::Drawing::Point(265, 50);
    this->lblFilterRole->Name = L"lblFilterRole";
    this->lblFilterRole->Size = System::Drawing::Size(57, 13);
    this->lblFilterRole->TabIndex = 7;
    this->lblFilterRole->Text = L"Filter Role:";
    //
    // cmbFilterRole
    //
    this->cmbFilterRole->DropDownStyle =
        System::Windows::Forms::ComboBoxStyle::DropDownList;
    this->cmbFilterRole->Items->AddRange(gcnew cli::array<System::Object ^>(5){
        L"Semua", L"Admin", L"Merchant", L"Customer", L"Courier"});
    this->cmbFilterRole->Location = System::Drawing::Point(330, 47);
    this->cmbFilterRole->Name = L"cmbFilterRole";
    this->cmbFilterRole->Size = System::Drawing::Size(120, 21);
    this->cmbFilterRole->TabIndex = 8;
    this->cmbFilterRole->SelectedIndexChanged += gcnew System::EventHandler(
        this, &adminForm::cmbFilterRole_SelectedIndexChanged);
    //
    // btnAddUser
    //
    this->btnAddUser->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnAddUser->ForeColor = System::Drawing::Color::White;
    this->btnAddUser->Location = System::Drawing::Point(505, 408);
    this->btnAddUser->Name = L"btnAddUser";
    this->btnAddUser->Size = System::Drawing::Size(120, 30);
    this->btnAddUser->TabIndex = 5;
    this->btnAddUser->Text = L"+ Tambah User";
    this->btnAddUser->UseVisualStyleBackColor = false;
    this->btnAddUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnAddUser_Click);
    //
    // panelAddUser
    //
    this->panelAddUser->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(245)),
        static_cast<System::Int32>(static_cast<System::Byte>(250)),
        static_cast<System::Int32>(static_cast<System::Byte>(245)));
    this->panelAddUser->BorderStyle =
        System::Windows::Forms::BorderStyle::FixedSingle;
    this->panelAddUser->Controls->Add(this->lblNewUsername);
    this->panelAddUser->Controls->Add(this->txtNewUsername);
    this->panelAddUser->Controls->Add(this->lblNewPassword);
    this->panelAddUser->Controls->Add(this->txtNewPassword);
    this->panelAddUser->Controls->Add(this->lblNewRole);
    this->panelAddUser->Controls->Add(this->cmbNewRole);
    this->panelAddUser->Controls->Add(this->btnSaveUser);
    this->panelAddUser->Controls->Add(this->btnCancelAddUser);
    this->panelAddUser->Location = System::Drawing::Point(15, 50);
    this->panelAddUser->Name = L"panelAddUser";
    this->panelAddUser->Size = System::Drawing::Size(200, 250);
    this->panelAddUser->TabIndex = 9;
    this->panelAddUser->Visible = false;
    //
    // lblNewUsername
    //
    this->lblNewUsername->AutoSize = true;
    this->lblNewUsername->Location = System::Drawing::Point(15, 15);
    this->lblNewUsername->Name = L"lblNewUsername";
    this->lblNewUsername->Size = System::Drawing::Size(58, 13);
    this->lblNewUsername->TabIndex = 0;
    this->lblNewUsername->Text = L"Username:";
    //
    // txtNewUsername
    //
    this->txtNewUsername->Location = System::Drawing::Point(15, 35);
    this->txtNewUsername->Name = L"txtNewUsername";
    this->txtNewUsername->Size = System::Drawing::Size(160, 20);
    this->txtNewUsername->TabIndex = 1;
    //
    // lblNewPassword
    //
    this->lblNewPassword->AutoSize = true;
    this->lblNewPassword->Location = System::Drawing::Point(15, 70);
    this->lblNewPassword->Name = L"lblNewPassword";
    this->lblNewPassword->Size = System::Drawing::Size(56, 13);
    this->lblNewPassword->TabIndex = 2;
    this->lblNewPassword->Text = L"Password:";
    //
    // txtNewPassword
    //
    this->txtNewPassword->Location = System::Drawing::Point(15, 90);
    this->txtNewPassword->Name = L"txtNewPassword";
    this->txtNewPassword->PasswordChar = '*';
    this->txtNewPassword->Size = System::Drawing::Size(160, 20);
    this->txtNewPassword->TabIndex = 3;
    //
    // lblNewRole
    //
    this->lblNewRole->AutoSize = true;
    this->lblNewRole->Location = System::Drawing::Point(15, 125);
    this->lblNewRole->Name = L"lblNewRole";
    this->lblNewRole->Size = System::Drawing::Size(32, 13);
    this->lblNewRole->TabIndex = 4;
    this->lblNewRole->Text = L"Role:";
    //
    // cmbNewRole
    //
    this->cmbNewRole->DropDownStyle =
        System::Windows::Forms::ComboBoxStyle::DropDownList;
    this->cmbNewRole->Items->AddRange(gcnew cli::array<System::Object ^>(4){
        L"Admin", L"Merchant", L"Customer", L"Courier"});
    this->cmbNewRole->Location = System::Drawing::Point(15, 145);
    this->cmbNewRole->Name = L"cmbNewRole";
    this->cmbNewRole->Size = System::Drawing::Size(160, 21);
    this->cmbNewRole->TabIndex = 5;
    //
    // btnSaveUser
    //
    this->btnSaveUser->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnSaveUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnSaveUser->ForeColor = System::Drawing::Color::White;
    this->btnSaveUser->Location = System::Drawing::Point(15, 190);
    this->btnSaveUser->Name = L"btnSaveUser";
    this->btnSaveUser->Size = System::Drawing::Size(75, 30);
    this->btnSaveUser->TabIndex = 6;
    this->btnSaveUser->Text = L"Simpan";
    this->btnSaveUser->UseVisualStyleBackColor = false;
    this->btnSaveUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnSaveUser_Click);
    //
    // btnCancelAddUser
    //
    this->btnCancelAddUser->Location = System::Drawing::Point(100, 190);
    this->btnCancelAddUser->Name = L"btnCancelAddUser";
    this->btnCancelAddUser->Size = System::Drawing::Size(75, 30);
    this->btnCancelAddUser->TabIndex = 7;
    this->btnCancelAddUser->Text = L"Batal";
    this->btnCancelAddUser->Click +=
        gcnew System::EventHandler(this, &adminForm::btnCancelAddUser_Click);
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
    this->tabIncome->Size = System::Drawing::Size(852, 455);
    this->tabIncome->TabIndex = 2;
    this->tabIncome->Text = L"Income";
    this->tabIncome->UseVisualStyleBackColor = true;
    //
    // lblIncomeTitle
    //
    this->lblIncomeTitle->AutoSize = true;
    this->lblIncomeTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblIncomeTitle->Location = System::Drawing::Point(15, 15);
    this->lblIncomeTitle->Name = L"lblIncomeTitle";
    this->lblIncomeTitle->Size = System::Drawing::Size(154, 25);
    this->lblIncomeTitle->TabIndex = 0;
    this->lblIncomeTitle->Text = L"Income Records";
    //
    // lblTotalIncomeValue
    //
    this->lblTotalIncomeValue->AutoSize = true;
    this->lblTotalIncomeValue->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
    this->lblTotalIncomeValue->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblTotalIncomeValue->Location = System::Drawing::Point(175, 18);
    this->lblTotalIncomeValue->Name = L"lblTotalIncomeValue";
    this->lblTotalIncomeValue->Size = System::Drawing::Size(89, 21);
    this->lblTotalIncomeValue->TabIndex = 1;
    this->lblTotalIncomeValue->Text = L"Total: Rp 0";
    //
    // dgvIncome
    //
    this->dgvIncome->AllowUserToAddRows = false;
    this->dgvIncome->AllowUserToDeleteRows = false;
    this->dgvIncome->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvIncome->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvIncome->Location = System::Drawing::Point(15, 50);
    this->dgvIncome->MultiSelect = false;
    this->dgvIncome->Name = L"dgvIncome";
    this->dgvIncome->ReadOnly = true;
    this->dgvIncome->Size = System::Drawing::Size(820, 340);
    this->dgvIncome->TabIndex = 0;
    //
    // btnRefreshIncome
    //
    this->btnRefreshIncome->Location = System::Drawing::Point(15, 407);
    this->btnRefreshIncome->Name = L"btnRefreshIncome";
    this->btnRefreshIncome->Size = System::Drawing::Size(100, 30);
    this->btnRefreshIncome->TabIndex = 2;
    this->btnRefreshIncome->Text = L"Refresh";
    this->btnRefreshIncome->Click +=
        gcnew System::EventHandler(this, &adminForm::btnRefreshIncome_Click);
    //
    // tabTransactions
    //
    this->tabTransactions->Controls->Add(this->lblTransactionTitle);
    this->tabTransactions->Controls->Add(this->dgvTransactions);
    this->tabTransactions->Controls->Add(this->btnRefreshTransactions);
    this->tabTransactions->Controls->Add(this->lblFilterStatus);
    this->tabTransactions->Controls->Add(this->cmbFilterStatus);
    this->tabTransactions->Controls->Add(this->btnEditTransactionStatus);
    this->tabTransactions->Controls->Add(this->btnDeleteTransaction);
    this->tabTransactions->Location = System::Drawing::Point(4, 22);
    this->tabTransactions->Name = L"tabTransactions";
    this->tabTransactions->Padding = System::Windows::Forms::Padding(3);
    this->tabTransactions->Size = System::Drawing::Size(852, 455);
    this->tabTransactions->TabIndex = 3;
    this->tabTransactions->Text = L"Transactions";
    this->tabTransactions->UseVisualStyleBackColor = true;
    //
    // lblTransactionTitle
    //
    this->lblTransactionTitle->AutoSize = true;
    this->lblTransactionTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
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
    this->dgvTransactions->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvTransactions->ColumnHeadersHeightSizeMode = System::Windows::
        Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvTransactions->Location = System::Drawing::Point(15, 50);
    this->dgvTransactions->MultiSelect = false;
    this->dgvTransactions->Name = L"dgvTransactions";
    this->dgvTransactions->ReadOnly = true;
    this->dgvTransactions->SelectionMode =
        System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->dgvTransactions->Size = System::Drawing::Size(820, 340);
    this->dgvTransactions->TabIndex = 0;
    //
    // btnRefreshTransactions
    //
    this->btnRefreshTransactions->Location = System::Drawing::Point(15, 407);
    this->btnRefreshTransactions->Name = L"btnRefreshTransactions";
    this->btnRefreshTransactions->Size = System::Drawing::Size(100, 30);
    this->btnRefreshTransactions->TabIndex = 1;
    this->btnRefreshTransactions->Text = L"Refresh";
    this->btnRefreshTransactions->Click += gcnew System::EventHandler(
        this, &adminForm::btnRefreshTransactions_Click);
    //
    // lblFilterStatus
    //
    this->lblFilterStatus->AutoSize = true;
    this->lblFilterStatus->Location = System::Drawing::Point(250, 20);
    this->lblFilterStatus->Name = L"lblFilterStatus";
    this->lblFilterStatus->Size = System::Drawing::Size(65, 13);
    this->lblFilterStatus->TabIndex = 2;
    this->lblFilterStatus->Text = L"Filter Status:";
    //
    // cmbFilterStatus
    //
    this->cmbFilterStatus->DropDownStyle =
        System::Windows::Forms::ComboBoxStyle::DropDownList;
    this->cmbFilterStatus->Items->AddRange(gcnew cli::array<System::Object ^>(
        5){L"Semua", L"pending", L"shipping", L"delivered", L"cancelled"});
    this->cmbFilterStatus->Location = System::Drawing::Point(325, 17);
    this->cmbFilterStatus->Name = L"cmbFilterStatus";
    this->cmbFilterStatus->Size = System::Drawing::Size(120, 21);
    this->cmbFilterStatus->TabIndex = 3;
    this->cmbFilterStatus->SelectedIndexChanged += gcnew System::EventHandler(
        this, &adminForm::cmbFilterStatus_SelectedIndexChanged);
    //
    // btnEditTransactionStatus
    //
    this->btnEditTransactionStatus->BackColor = System::Drawing::Color::White;
    this->btnEditTransactionStatus->ForeColor = System::Drawing::Color::Black;
    this->btnEditTransactionStatus->Location = System::Drawing::Point(130, 407);
    this->btnEditTransactionStatus->Name = L"btnEditTransactionStatus";
    this->btnEditTransactionStatus->Size = System::Drawing::Size(140, 30);
    this->btnEditTransactionStatus->TabIndex = 2;
    this->btnEditTransactionStatus->Text = L"Ubah Status Transaksi";
    this->btnEditTransactionStatus->UseVisualStyleBackColor = false;
    this->btnEditTransactionStatus->Click += gcnew System::EventHandler(
        this, &adminForm::btnEditTransactionStatus_Click);
    //
    // btnDeleteTransaction
    //
    this->btnDeleteTransaction->BackColor = System::Drawing::Color::White;
    this->btnDeleteTransaction->ForeColor = System::Drawing::Color::Black;
    this->btnDeleteTransaction->Location = System::Drawing::Point(285, 407);
    this->btnDeleteTransaction->Name = L"btnDeleteTransaction";
    this->btnDeleteTransaction->Size = System::Drawing::Size(130, 30);
    this->btnDeleteTransaction->TabIndex = 4;
    this->btnDeleteTransaction->Text = L"Hapus Transaksi";
    this->btnDeleteTransaction->UseVisualStyleBackColor = false;
    this->btnDeleteTransaction->Click += gcnew System::EventHandler(
        this, &adminForm::btnDeleteTransaction_Click);
    //
    // tabProducts
    //
    this->tabProducts->Controls->Add(this->lblProductsTitle);
    this->tabProducts->Controls->Add(this->dgvProducts);
    this->tabProducts->Controls->Add(this->btnRefreshProducts);
    this->tabProducts->Controls->Add(this->btnEditProduct);
    this->tabProducts->Controls->Add(this->btnDeleteProduct);
    this->tabProducts->Controls->Add(this->panelEditProduct);
    this->tabProducts->Location = System::Drawing::Point(4, 22);
    this->tabProducts->Name = L"tabProducts";
    this->tabProducts->Padding = System::Windows::Forms::Padding(3);
    this->tabProducts->Size = System::Drawing::Size(852, 455);
    this->tabProducts->TabIndex = 4;
    this->tabProducts->Text = L"Products";
    this->tabProducts->UseVisualStyleBackColor = true;
    //
    // lblProductsTitle
    //
    this->lblProductsTitle->AutoSize = true;
    this->lblProductsTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblProductsTitle->Location = System::Drawing::Point(18, 18);
    this->lblProductsTitle->Name = L"lblProductsTitle";
    this->lblProductsTitle->Size = System::Drawing::Size(207, 25);
    this->lblProductsTitle->TabIndex = 0;
    this->lblProductsTitle->Text = L"Product Management";
    //
    // dgvProducts
    //
    this->dgvProducts->AllowUserToAddRows = false;
    this->dgvProducts->AllowUserToDeleteRows = false;
    this->dgvProducts->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvProducts->Location = System::Drawing::Point(15, 50);
    this->dgvProducts->MultiSelect = false;
    this->dgvProducts->Name = L"dgvProducts";
    this->dgvProducts->ReadOnly = true;
    this->dgvProducts->SelectionMode =
        System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->dgvProducts->Size = System::Drawing::Size(820, 340);
    this->dgvProducts->TabIndex = 0;
    //
    // btnRefreshProducts
    //
    this->btnRefreshProducts->Location = System::Drawing::Point(15, 407);
    this->btnRefreshProducts->Name = L"btnRefreshProducts";
    this->btnRefreshProducts->Size = System::Drawing::Size(100, 30);
    this->btnRefreshProducts->TabIndex = 1;
    this->btnRefreshProducts->Text = L"Refresh";
    this->btnRefreshProducts->Click +=
        gcnew System::EventHandler(this, &adminForm::btnRefreshProducts_Click);
    //
    // btnEditProduct
    //
    this->btnEditProduct->BackColor = System::Drawing::Color::White;
    this->btnEditProduct->ForeColor = System::Drawing::Color::Black;
    this->btnEditProduct->Location = System::Drawing::Point(130, 407);
    this->btnEditProduct->Name = L"btnEditProduct";
    this->btnEditProduct->Size = System::Drawing::Size(100, 30);
    this->btnEditProduct->TabIndex = 2;
    this->btnEditProduct->Text = L"Edit Produk";
    this->btnEditProduct->UseVisualStyleBackColor = false;
    this->btnEditProduct->Click +=
        gcnew System::EventHandler(this, &adminForm::btnEditProduct_Click);
    //
    // btnDeleteProduct
    //
    this->btnDeleteProduct->BackColor = System::Drawing::Color::White;
    this->btnDeleteProduct->ForeColor = System::Drawing::Color::Black;
    this->btnDeleteProduct->Location = System::Drawing::Point(245, 407);
    this->btnDeleteProduct->Name = L"btnDeleteProduct";
    this->btnDeleteProduct->Size = System::Drawing::Size(100, 30);
    this->btnDeleteProduct->TabIndex = 3;
    this->btnDeleteProduct->Text = L"Hapus Produk";
    this->btnDeleteProduct->UseVisualStyleBackColor = false;
    this->btnDeleteProduct->Click +=
        gcnew System::EventHandler(this, &adminForm::btnDeleteProduct_Click);
    //
    // panelEditProduct
    //
    this->panelEditProduct->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(245)),
        static_cast<System::Int32>(static_cast<System::Byte>(250)),
        static_cast<System::Int32>(static_cast<System::Byte>(245)));
    this->panelEditProduct->BorderStyle =
        System::Windows::Forms::BorderStyle::FixedSingle;
    this->panelEditProduct->Controls->Add(this->lblEditProductName);
    this->panelEditProduct->Controls->Add(this->txtEditProductName);
    this->panelEditProduct->Controls->Add(this->lblEditProductPrice);
    this->panelEditProduct->Controls->Add(this->txtEditProductPrice);
    this->panelEditProduct->Controls->Add(this->lblEditProductStock);
    this->panelEditProduct->Controls->Add(this->txtEditProductStock);
    this->panelEditProduct->Controls->Add(this->lblEditProductKategori);
    this->panelEditProduct->Controls->Add(this->txtEditProductKategori);
    this->panelEditProduct->Controls->Add(this->lblEditProductDeskripsi);
    this->panelEditProduct->Controls->Add(this->txtEditProductDeskripsi);
    this->panelEditProduct->Controls->Add(this->btnSaveProduct);
    this->panelEditProduct->Controls->Add(this->btnCancelEditProduct);
    this->panelEditProduct->Location = System::Drawing::Point(15, 50);
    this->panelEditProduct->Name = L"panelEditProduct";
    this->panelEditProduct->Size = System::Drawing::Size(200, 350);
    this->panelEditProduct->TabIndex = 4;
    this->panelEditProduct->Visible = false;
    //
    // lblEditProductName
    //
    this->lblEditProductName->AutoSize = true;
    this->lblEditProductName->Location = System::Drawing::Point(15, 15);
    this->lblEditProductName->Name = L"lblEditProductName";
    this->lblEditProductName->Size = System::Drawing::Size(75, 13);
    this->lblEditProductName->TabIndex = 0;
    this->lblEditProductName->Text = L"Nama Produk:";
    //
    // txtEditProductName
    //
    this->txtEditProductName->Location = System::Drawing::Point(15, 35);
    this->txtEditProductName->Name = L"txtEditProductName";
    this->txtEditProductName->Size = System::Drawing::Size(160, 20);
    this->txtEditProductName->TabIndex = 1;
    //
    // lblEditProductPrice
    //
    this->lblEditProductPrice->AutoSize = true;
    this->lblEditProductPrice->Location = System::Drawing::Point(15, 65);
    this->lblEditProductPrice->Name = L"lblEditProductPrice";
    this->lblEditProductPrice->Size = System::Drawing::Size(39, 13);
    this->lblEditProductPrice->TabIndex = 2;
    this->lblEditProductPrice->Text = L"Harga:";
    //
    // txtEditProductPrice
    //
    this->txtEditProductPrice->Location = System::Drawing::Point(15, 85);
    this->txtEditProductPrice->Name = L"txtEditProductPrice";
    this->txtEditProductPrice->Size = System::Drawing::Size(160, 20);
    this->txtEditProductPrice->TabIndex = 3;
    //
    // lblEditProductStock
    //
    this->lblEditProductStock->AutoSize = true;
    this->lblEditProductStock->Location = System::Drawing::Point(15, 115);
    this->lblEditProductStock->Name = L"lblEditProductStock";
    this->lblEditProductStock->Size = System::Drawing::Size(32, 13);
    this->lblEditProductStock->TabIndex = 4;
    this->lblEditProductStock->Text = L"Stok:";
    //
    // txtEditProductStock
    //
    this->txtEditProductStock->Location = System::Drawing::Point(15, 135);
    this->txtEditProductStock->Name = L"txtEditProductStock";
    this->txtEditProductStock->Size = System::Drawing::Size(160, 20);
    this->txtEditProductStock->TabIndex = 5;
    //
    // lblEditProductKategori
    //
    this->lblEditProductKategori->AutoSize = true;
    this->lblEditProductKategori->Location = System::Drawing::Point(15, 165);
    this->lblEditProductKategori->Name = L"lblEditProductKategori";
    this->lblEditProductKategori->Size = System::Drawing::Size(52, 13);
    this->lblEditProductKategori->TabIndex = 8;
    this->lblEditProductKategori->Text = L"Kategori:";
    //
    // txtEditProductKategori
    //
    this->txtEditProductKategori->Location = System::Drawing::Point(15, 185);
    this->txtEditProductKategori->Name = L"txtEditProductKategori";
    this->txtEditProductKategori->Size = System::Drawing::Size(160, 20);
    this->txtEditProductKategori->TabIndex = 9;
    //
    // lblEditProductDeskripsi
    //
    this->lblEditProductDeskripsi->AutoSize = true;
    this->lblEditProductDeskripsi->Location = System::Drawing::Point(15, 215);
    this->lblEditProductDeskripsi->Name = L"lblEditProductDeskripsi";
    this->lblEditProductDeskripsi->Size = System::Drawing::Size(57, 13);
    this->lblEditProductDeskripsi->TabIndex = 10;
    this->lblEditProductDeskripsi->Text = L"Deskripsi:";
    //
    // txtEditProductDeskripsi
    //
    this->txtEditProductDeskripsi->Location = System::Drawing::Point(15, 235);
    this->txtEditProductDeskripsi->Multiline = true;
    this->txtEditProductDeskripsi->Name = L"txtEditProductDeskripsi";
    this->txtEditProductDeskripsi->Size = System::Drawing::Size(160, 45);
    this->txtEditProductDeskripsi->TabIndex = 11;
    //
    // btnSaveProduct
    //
    this->btnSaveProduct->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnSaveProduct->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnSaveProduct->ForeColor = System::Drawing::Color::White;
    this->btnSaveProduct->Location = System::Drawing::Point(15, 295);
    this->btnSaveProduct->Name = L"btnSaveProduct";
    this->btnSaveProduct->Size = System::Drawing::Size(75, 30);
    this->btnSaveProduct->TabIndex = 6;
    this->btnSaveProduct->Text = L"Simpan";
    this->btnSaveProduct->UseVisualStyleBackColor = false;
    this->btnSaveProduct->Click +=
        gcnew System::EventHandler(this, &adminForm::btnSaveProduct_Click);
    //
    // btnCancelEditProduct
    //
    this->btnCancelEditProduct->Location = System::Drawing::Point(100, 295);
    this->btnCancelEditProduct->Name = L"btnCancelEditProduct";
    this->btnCancelEditProduct->Size = System::Drawing::Size(75, 30);
    this->btnCancelEditProduct->TabIndex = 7;
    this->btnCancelEditProduct->Text = L"Batal";
    this->btnCancelEditProduct->Click += gcnew System::EventHandler(
        this, &adminForm::btnCancelEditProduct_Click);
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
    this->btnLogout->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(220)),
        static_cast<System::Int32>(static_cast<System::Byte>(53)),
        static_cast<System::Int32>(static_cast<System::Byte>(69)));
    this->btnLogout->FlatAppearance->BorderSize = 0;
    this->btnLogout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnLogout->ForeColor = System::Drawing::Color::White;
    this->btnLogout->Location = System::Drawing::Point(758, 499);
    this->btnLogout->Name = L"btnLogout";
    this->btnLogout->Size = System::Drawing::Size(110, 30);
    this->btnLogout->TabIndex = 1;
    this->btnLogout->Text = L"Logout";
    this->btnLogout->UseVisualStyleBackColor = false;
    this->btnLogout->Click +=
        gcnew System::EventHandler(this, &adminForm::btnLogout_Click);
    //
    // contextMenuStrip1
    //
    this->contextMenuStrip1->Name = L"contextMenuStrip1";
    this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
    //
    // label1
    //
    this->label1->AutoSize = true;
    this->label1->Location = System::Drawing::Point(528, 131);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(90, 13);
    this->label1->TabIndex = 18;
    this->label1->Text = L"Masukan Jumlah:";
    //
    // adminForm
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->BackColor = System::Drawing::Color::FloralWhite;
    this->ClientSize = System::Drawing::Size(884, 541);
    this->Controls->Add(this->tabControl);
    this->Controls->Add(this->btnLogout);
    this->FormBorderStyle =
        System::Windows::Forms::FormBorderStyle::FixedSingle;
    this->MaximizeBox = false;
    this->Name = L"adminForm";
    this->StartPosition =
        System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Admin Dashboard - E-Commerce";
    this->Load += gcnew System::EventHandler(this, &adminForm::adminForm_Load);
    this->tabControl->ResumeLayout(false);
    this->tabDashboard->ResumeLayout(false);
    this->tabDashboard->PerformLayout();
    this->tabUsers->ResumeLayout(false);
    this->tabUsers->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvUsers))
        ->EndInit();
    this->panelAddUser->ResumeLayout(false);
    this->panelAddUser->PerformLayout();
    this->tabIncome->ResumeLayout(false);
    this->tabIncome->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvIncome))
        ->EndInit();
    this->tabTransactions->ResumeLayout(false);
    this->tabTransactions->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvTransactions))
        ->EndInit();
    this->tabProducts->ResumeLayout(false);
    this->tabProducts->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvProducts))
        ->EndInit();
    this->panelEditProduct->ResumeLayout(false);
    this->panelEditProduct->PerformLayout();
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
  System::Void btnAddUser_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnSaveUser_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  System::Void btnCancelAddUser_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  void ClearAddUserForm();

  // User search and filter
  System::Void txtSearchUser_TextChanged(System::Object ^ sender,
                                         System::EventArgs ^ e);
  System::Void cmbFilterRole_SelectedIndexChanged(System::Object ^ sender,
                                                  System::EventArgs ^ e);
  void FilterUsers();

  // Products management
  void LoadProducts();
  System::Void btnRefreshProducts_Click(System::Object ^ sender,
                                        System::EventArgs ^ e);
  System::Void btnEditProduct_Click(System::Object ^ sender,
                                    System::EventArgs ^ e);
  System::Void btnDeleteProduct_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  System::Void btnSaveProduct_Click(System::Object ^ sender,
                                    System::EventArgs ^ e);
  System::Void btnCancelEditProduct_Click(System::Object ^ sender,
                                          System::EventArgs ^ e);
  void ClearEditProductForm();

  // Transaction status edit
  System::Void btnEditTransactionStatus_Click(System::Object ^ sender,
                                              System::EventArgs ^ e);
  System::Void btnDeleteTransaction_Click(System::Object ^ sender,
                                          System::EventArgs ^ e);
  System::Void cmbFilterStatus_SelectedIndexChanged(System::Object ^ sender,
                                                    System::EventArgs ^ e);
  void FilterTransactions();

private:
  System::Void lblTotalTransactions_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {}

private:
  System::Void lblAppIncome_Click(System::Object ^ sender,
                                  System::EventArgs ^ e) {}

private:
  System::Void btnAdminWithdraw_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
};
} // namespace ECommerce
