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
/// Customer Dashboard - Browse and buy products
/// </summary>
public
ref class customerForm : public System::Windows::Forms::Form {
public:
  int currentUserID;
  String ^ currentUsername;

private:
  System::Windows::Forms::Label ^ lblSaldoTitle;

public:
private:
  System::Windows::Forms::Label ^ lblCurrentSaldo;

private:
  System::Windows::Forms::Label ^ lblTopUpAmount;

private:
  System::Windows::Forms::TextBox ^ txtTopUpAmount;

private:
  System::Windows::Forms::Button ^ btnTopUp;
  int currentSaldo;

public:
  customerForm(void) {
    InitializeComponent();
    currentUserID = 0;
    currentUsername = "";
    currentSaldo = 0;
    // Initialize cart DataTable
    cartTable = gcnew DataTable();
    cartTable->Columns->Add("ID", Int32::typeid);
    cartTable->Columns->Add("Nama", String::typeid);
    cartTable->Columns->Add("Harga", Int32::typeid);
    cartTable->Columns->Add("Jumlah", Int32::typeid);
    cartTable->Columns->Add("Total", Int32::typeid);
  }

  customerForm(int userID, String ^ username) {
    InitializeComponent();
    currentUserID = userID;
    currentUsername = username;
    currentSaldo = 0;
    // Initialize cart DataTable
    cartTable = gcnew DataTable();
    cartTable->Columns->Add("ID", Int32::typeid);
    cartTable->Columns->Add("Nama", String::typeid);
    cartTable->Columns->Add("Harga", Int32::typeid);
    cartTable->Columns->Add("Jumlah", Int32::typeid);
    cartTable->Columns->Add("Total", Int32::typeid);
  }

protected:
  ~customerForm() {
    if (components) {
      delete components;
    }
  }

private:
  System::Windows::Forms::TabControl ^ tabControl;

private:
  System::Windows::Forms::TabPage ^ tabCatalog;

private:
  System::Windows::Forms::TabPage ^ tabHistory;

private:
  System::Windows::Forms::TabPage ^ tabCart;

private:
  DataTable ^ cartTable;

private:
  // Catalog
private:
  System::Windows::Forms::Label ^ lblCatalogTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvProducts;

private:
  System::Windows::Forms::Button ^ btnRefreshCatalog;

private:
  System::Windows::Forms::Button ^ btnBuy;

private:
  System::Windows::Forms::Label ^ lblSaldoInfo;

private:
  System::Windows::Forms::NumericUpDown ^ nudQuantity;

private:
  System::Windows::Forms::Label ^ lblQuantity;

private:
  System::Windows::Forms::Button ^ btnAddToCart;

  // Cart Tab Controls
private:
  System::Windows::Forms::Label ^ lblCartTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvCart;

private:
  System::Windows::Forms::Button ^ btnRemoveFromCart;

private:
  System::Windows::Forms::Button ^ btnCheckout;

private:
  System::Windows::Forms::Label ^ lblCartTotal;

  // History
private:
  System::Windows::Forms::Label ^ lblHistoryTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvHistory;

private:
  System::Windows::Forms::Button ^ btnRefreshHistory;

  // Saldo
private:
private:
private:
private:
private:
private:
  System::Windows::Forms::TabPage ^ tabProfile;

private:
  System::Windows::Forms::Label ^ lblProfileTitle;

private:
  System::Windows::Forms::Label ^ lblAlamat;

private:
  System::Windows::Forms::TextBox ^ txtAlamat;

private:
  System::Windows::Forms::Button ^ btnSaveAlamat;

private:
  System::Windows::Forms::Label ^ lblAlamatInfo;

private:
  System::Windows::Forms::Button ^ btnLogout;

private:
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
    this->tabControl = (gcnew System::Windows::Forms::TabControl());
    this->tabCatalog = (gcnew System::Windows::Forms::TabPage());
    this->lblCatalogTitle = (gcnew System::Windows::Forms::Label());
    this->dgvProducts = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshCatalog = (gcnew System::Windows::Forms::Button());
    this->lblQuantity = (gcnew System::Windows::Forms::Label());
    this->nudQuantity = (gcnew System::Windows::Forms::NumericUpDown());
    this->btnAddToCart = (gcnew System::Windows::Forms::Button());
    this->lblSaldoInfo = (gcnew System::Windows::Forms::Label());
    this->tabCart = (gcnew System::Windows::Forms::TabPage());
    this->lblCartTitle = (gcnew System::Windows::Forms::Label());
    this->dgvCart = (gcnew System::Windows::Forms::DataGridView());
    this->btnRemoveFromCart = (gcnew System::Windows::Forms::Button());
    this->btnCheckout = (gcnew System::Windows::Forms::Button());
    this->lblCartTotal = (gcnew System::Windows::Forms::Label());
    this->tabHistory = (gcnew System::Windows::Forms::TabPage());
    this->lblHistoryTitle = (gcnew System::Windows::Forms::Label());
    this->dgvHistory = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshHistory = (gcnew System::Windows::Forms::Button());
    this->tabProfile = (gcnew System::Windows::Forms::TabPage());
    this->lblSaldoTitle = (gcnew System::Windows::Forms::Label());
    this->lblCurrentSaldo = (gcnew System::Windows::Forms::Label());
    this->lblTopUpAmount = (gcnew System::Windows::Forms::Label());
    this->txtTopUpAmount = (gcnew System::Windows::Forms::TextBox());
    this->btnTopUp = (gcnew System::Windows::Forms::Button());
    this->lblProfileTitle = (gcnew System::Windows::Forms::Label());
    this->lblAlamat = (gcnew System::Windows::Forms::Label());
    this->txtAlamat = (gcnew System::Windows::Forms::TextBox());
    this->btnSaveAlamat = (gcnew System::Windows::Forms::Button());
    this->lblAlamatInfo = (gcnew System::Windows::Forms::Label());
    this->btnLogout = (gcnew System::Windows::Forms::Button());
    this->tabControl->SuspendLayout();
    this->tabCatalog->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvProducts))
        ->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->nudQuantity))
        ->BeginInit();
    this->tabCart->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvCart))
        ->BeginInit();
    this->tabHistory->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvHistory))
        ->BeginInit();
    this->tabProfile->SuspendLayout();
    this->SuspendLayout();
    //
    // tabControl
    //
    this->tabControl->Controls->Add(this->tabCatalog);
    this->tabControl->Controls->Add(this->tabCart);
    this->tabControl->Controls->Add(this->tabHistory);
    this->tabControl->Controls->Add(this->tabProfile);
    this->tabControl->Location = System::Drawing::Point(12, 12);
    this->tabControl->Name = L"tabControl";
    this->tabControl->SelectedIndex = 0;
    this->tabControl->Size = System::Drawing::Size(860, 480);
    this->tabControl->TabIndex = 0;
    //
    // tabCatalog
    //
    this->tabCatalog->Controls->Add(this->lblCatalogTitle);
    this->tabCatalog->Controls->Add(this->dgvProducts);
    this->tabCatalog->Controls->Add(this->btnRefreshCatalog);
    this->tabCatalog->Controls->Add(this->lblQuantity);
    this->tabCatalog->Controls->Add(this->nudQuantity);
    this->tabCatalog->Controls->Add(this->btnAddToCart);
    this->tabCatalog->Controls->Add(this->lblSaldoInfo);
    this->tabCatalog->Location = System::Drawing::Point(4, 22);
    this->tabCatalog->Name = L"tabCatalog";
    this->tabCatalog->Padding = System::Windows::Forms::Padding(3);
    this->tabCatalog->Size = System::Drawing::Size(852, 454);
    this->tabCatalog->TabIndex = 0;
    this->tabCatalog->Text = L"Katalog Produk";
    this->tabCatalog->UseVisualStyleBackColor = true;
    //
    // lblCatalogTitle
    //
    this->lblCatalogTitle->AutoSize = true;
    this->lblCatalogTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblCatalogTitle->ForeColor = System::Drawing::Color::Black;
    this->lblCatalogTitle->Location = System::Drawing::Point(15, 15);
    this->lblCatalogTitle->Name = L"lblCatalogTitle";
    this->lblCatalogTitle->Size = System::Drawing::Size(152, 25);
    this->lblCatalogTitle->TabIndex = 0;
    this->lblCatalogTitle->Text = L"Katalog Produk";
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
    this->dgvProducts->Size = System::Drawing::Size(815, 348);
    this->dgvProducts->TabIndex = 1;
    //
    // btnRefreshCatalog
    //
    this->btnRefreshCatalog->Location = System::Drawing::Point(15, 406);
    this->btnRefreshCatalog->Name = L"btnRefreshCatalog";
    this->btnRefreshCatalog->Size = System::Drawing::Size(100, 30);
    this->btnRefreshCatalog->TabIndex = 2;
    this->btnRefreshCatalog->Text = L"Refresh";
    this->btnRefreshCatalog->UseVisualStyleBackColor = true;
    this->btnRefreshCatalog->Click += gcnew System::EventHandler(
        this, &customerForm::btnRefreshCatalog_Click);
    //
    // lblQuantity
    //
    this->lblQuantity->AutoSize = true;
    this->lblQuantity->Location = System::Drawing::Point(130, 411);
    this->lblQuantity->Name = L"lblQuantity";
    this->lblQuantity->Size = System::Drawing::Size(43, 13);
    this->lblQuantity->TabIndex = 3;
    this->lblQuantity->Text = L"Jumlah:";
    //
    // nudQuantity
    //
    this->nudQuantity->Location = System::Drawing::Point(185, 408);
    this->nudQuantity->Minimum =
        System::Decimal(gcnew cli::array<System::Int32>(4){1, 0, 0, 0});
    this->nudQuantity->Name = L"nudQuantity";
    this->nudQuantity->Size = System::Drawing::Size(60, 20);
    this->nudQuantity->TabIndex = 4;
    this->nudQuantity->Value =
        System::Decimal(gcnew cli::array<System::Int32>(4){1, 0, 0, 0});
    //
    // btnAddToCart
    //
    this->btnAddToCart->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(40)),
        static_cast<System::Int32>(static_cast<System::Byte>(167)),
        static_cast<System::Int32>(static_cast<System::Byte>(69)));
    this->btnAddToCart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnAddToCart->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnAddToCart->ForeColor = System::Drawing::Color::White;
    this->btnAddToCart->Location = System::Drawing::Point(260, 404);
    this->btnAddToCart->Name = L"btnAddToCart";
    this->btnAddToCart->Size = System::Drawing::Size(150, 30);
    this->btnAddToCart->TabIndex = 3;
    this->btnAddToCart->Text = L"+ Keranjang";
    this->btnAddToCart->UseVisualStyleBackColor = false;
    this->btnAddToCart->Click +=
        gcnew System::EventHandler(this, &customerForm::btnAddToCart_Click);
    //
    // lblSaldoInfo
    //
    this->lblSaldoInfo->AutoSize = true;
    this->lblSaldoInfo->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
    this->lblSaldoInfo->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblSaldoInfo->Location = System::Drawing::Point(550, 15);
    this->lblSaldoInfo->Name = L"lblSaldoInfo";
    this->lblSaldoInfo->Size = System::Drawing::Size(94, 21);
    this->lblSaldoInfo->TabIndex = 4;
    this->lblSaldoInfo->Text = L"Saldo: Rp 0";
    //
    // tabCart
    //
    this->tabCart->Controls->Add(this->lblCartTitle);
    this->tabCart->Controls->Add(this->dgvCart);
    this->tabCart->Controls->Add(this->btnRemoveFromCart);
    this->tabCart->Controls->Add(this->btnCheckout);
    this->tabCart->Controls->Add(this->lblCartTotal);
    this->tabCart->Location = System::Drawing::Point(4, 22);
    this->tabCart->Name = L"tabCart";
    this->tabCart->Size = System::Drawing::Size(852, 454);
    this->tabCart->TabIndex = 5;
    this->tabCart->Text = L"Keranjang";
    this->tabCart->UseVisualStyleBackColor = true;
    //
    // lblCartTitle
    //
    this->lblCartTitle->AutoSize = true;
    this->lblCartTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblCartTitle->Location = System::Drawing::Point(15, 15);
    this->lblCartTitle->Name = L"lblCartTitle";
    this->lblCartTitle->Size = System::Drawing::Size(172, 25);
    this->lblCartTitle->TabIndex = 0;
    this->lblCartTitle->Text = L"Keranjang Belanja";
    //
    // dgvCart
    //
    this->dgvCart->AllowUserToAddRows = false;
    this->dgvCart->AllowUserToDeleteRows = false;
    this->dgvCart->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvCart->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvCart->Location = System::Drawing::Point(15, 50);
    this->dgvCart->MultiSelect = false;
    this->dgvCart->Name = L"dgvCart";
    this->dgvCart->ReadOnly = true;
    this->dgvCart->SelectionMode =
        System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->dgvCart->Size = System::Drawing::Size(822, 342);
    this->dgvCart->TabIndex = 1;
    //
    // btnRemoveFromCart
    //
    this->btnRemoveFromCart->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(220)),
        static_cast<System::Int32>(static_cast<System::Byte>(53)),
        static_cast<System::Int32>(static_cast<System::Byte>(69)));
    this->btnRemoveFromCart->FlatStyle =
        System::Windows::Forms::FlatStyle::Flat;
    this->btnRemoveFromCart->ForeColor = System::Drawing::Color::White;
    this->btnRemoveFromCart->Location = System::Drawing::Point(717, 408);
    this->btnRemoveFromCart->Name = L"btnRemoveFromCart";
    this->btnRemoveFromCart->Size = System::Drawing::Size(120, 30);
    this->btnRemoveFromCart->TabIndex = 2;
    this->btnRemoveFromCart->Text = L"Hapus Item";
    this->btnRemoveFromCart->UseVisualStyleBackColor = false;
    this->btnRemoveFromCart->Click += gcnew System::EventHandler(
        this, &customerForm::btnRemoveFromCart_Click);
    //
    // btnCheckout
    //
    this->btnCheckout->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(40)),
        static_cast<System::Int32>(static_cast<System::Byte>(167)),
        static_cast<System::Int32>(static_cast<System::Byte>(69)));
    this->btnCheckout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnCheckout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
    this->btnCheckout->ForeColor = System::Drawing::Color::White;
    this->btnCheckout->Location = System::Drawing::Point(15, 402);
    this->btnCheckout->Name = L"btnCheckout";
    this->btnCheckout->Size = System::Drawing::Size(180, 40);
    this->btnCheckout->TabIndex = 3;
    this->btnCheckout->Text = L"Checkout";
    this->btnCheckout->UseVisualStyleBackColor = false;
    this->btnCheckout->Click +=
        gcnew System::EventHandler(this, &customerForm::btnCheckout_Click);
    //
    // lblCartTotal
    //
    this->lblCartTotal->AutoSize = true;
    this->lblCartTotal->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblCartTotal->Location = System::Drawing::Point(201, 408);
    this->lblCartTotal->Name = L"lblCartTotal";
    this->lblCartTotal->Size = System::Drawing::Size(105, 25);
    this->lblCartTotal->TabIndex = 4;
    this->lblCartTotal->Text = L"Total: Rp 0";
    //
    // tabHistory
    //
    this->tabHistory->Controls->Add(this->lblHistoryTitle);
    this->tabHistory->Controls->Add(this->dgvHistory);
    this->tabHistory->Controls->Add(this->btnRefreshHistory);
    this->tabHistory->Location = System::Drawing::Point(4, 22);
    this->tabHistory->Name = L"tabHistory";
    this->tabHistory->Size = System::Drawing::Size(852, 454);
    this->tabHistory->TabIndex = 1;
    this->tabHistory->Text = L"Riwayat Pembelian";
    this->tabHistory->UseVisualStyleBackColor = true;
    //
    // lblHistoryTitle
    //
    this->lblHistoryTitle->AutoSize = true;
    this->lblHistoryTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblHistoryTitle->ForeColor = System::Drawing::Color::Black;
    this->lblHistoryTitle->Location = System::Drawing::Point(10, 22);
    this->lblHistoryTitle->Name = L"lblHistoryTitle";
    this->lblHistoryTitle->Size = System::Drawing::Size(178, 25);
    this->lblHistoryTitle->TabIndex = 0;
    this->lblHistoryTitle->Text = L"Riwayat Pembelian";
    //
    // dgvHistory
    //
    this->dgvHistory->AllowUserToAddRows = false;
    this->dgvHistory->AllowUserToDeleteRows = false;
    this->dgvHistory->AutoSizeColumnsMode =
        System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->dgvHistory->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->dgvHistory->Location = System::Drawing::Point(15, 50);
    this->dgvHistory->Name = L"dgvHistory";
    this->dgvHistory->ReadOnly = true;
    this->dgvHistory->Size = System::Drawing::Size(820, 351);
    this->dgvHistory->TabIndex = 1;
    //
    // btnRefreshHistory
    //
    this->btnRefreshHistory->Location = System::Drawing::Point(15, 407);
    this->btnRefreshHistory->Name = L"btnRefreshHistory";
    this->btnRefreshHistory->Size = System::Drawing::Size(100, 30);
    this->btnRefreshHistory->TabIndex = 2;
    this->btnRefreshHistory->Text = L"Refresh";
    this->btnRefreshHistory->UseVisualStyleBackColor = true;
    this->btnRefreshHistory->Click += gcnew System::EventHandler(
        this, &customerForm::btnRefreshHistory_Click);
    //
    // tabProfile
    //
    this->tabProfile->Controls->Add(this->lblSaldoTitle);
    this->tabProfile->Controls->Add(this->lblCurrentSaldo);
    this->tabProfile->Controls->Add(this->lblTopUpAmount);
    this->tabProfile->Controls->Add(this->txtTopUpAmount);
    this->tabProfile->Controls->Add(this->btnTopUp);
    this->tabProfile->Controls->Add(this->lblProfileTitle);
    this->tabProfile->Controls->Add(this->lblAlamat);
    this->tabProfile->Controls->Add(this->txtAlamat);
    this->tabProfile->Controls->Add(this->btnSaveAlamat);
    this->tabProfile->Controls->Add(this->lblAlamatInfo);
    this->tabProfile->Location = System::Drawing::Point(4, 22);
    this->tabProfile->Name = L"tabProfile";
    this->tabProfile->Size = System::Drawing::Size(852, 454);
    this->tabProfile->TabIndex = 3;
    this->tabProfile->Text = L"Profil";
    this->tabProfile->UseVisualStyleBackColor = true;
    //
    // lblSaldoTitle
    //
    this->lblSaldoTitle->AutoSize = true;
    this->lblSaldoTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblSaldoTitle->Location = System::Drawing::Point(485, 55);
    this->lblSaldoTitle->Name = L"lblSaldoTitle";
    this->lblSaldoTitle->Size = System::Drawing::Size(173, 25);
    this->lblSaldoTitle->TabIndex = 5;
    this->lblSaldoTitle->Text = L"Kelola Saldo Anda";
    //
    // lblCurrentSaldo
    //
    this->lblCurrentSaldo->AutoSize = true;
    this->lblCurrentSaldo->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
    this->lblCurrentSaldo->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblCurrentSaldo->Location = System::Drawing::Point(484, 80);
    this->lblCurrentSaldo->Name = L"lblCurrentSaldo";
    this->lblCurrentSaldo->Size = System::Drawing::Size(143, 32);
    this->lblCurrentSaldo->TabIndex = 6;
    this->lblCurrentSaldo->Text = L"Saldo: Rp 0";
    //
    // lblTopUpAmount
    //
    this->lblTopUpAmount->AutoSize = true;
    this->lblTopUpAmount->Location = System::Drawing::Point(487, 129);
    this->lblTopUpAmount->Name = L"lblTopUpAmount";
    this->lblTopUpAmount->Size = System::Drawing::Size(105, 13);
    this->lblTopUpAmount->TabIndex = 7;
    this->lblTopUpAmount->Text = L"Jumlah Top Up (Rp):";
    //
    // txtTopUpAmount
    //
    this->txtTopUpAmount->Font =
        (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
    this->txtTopUpAmount->Location = System::Drawing::Point(487, 149);
    this->txtTopUpAmount->Name = L"txtTopUpAmount";
    this->txtTopUpAmount->Size = System::Drawing::Size(200, 26);
    this->txtTopUpAmount->TabIndex = 8;
    this->txtTopUpAmount->Text = L"100000";
    //
    // btnTopUp
    //
    this->btnTopUp->BackColor = System::Drawing::Color::Honeydew;
    this->btnTopUp->Font = (gcnew System::Drawing::Font(
        L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
    this->btnTopUp->Location = System::Drawing::Point(487, 189);
    this->btnTopUp->Name = L"btnTopUp";
    this->btnTopUp->Size = System::Drawing::Size(200, 35);
    this->btnTopUp->TabIndex = 9;
    this->btnTopUp->Text = L"Top Up Saldo";
    this->btnTopUp->UseVisualStyleBackColor = false;
    //
    // lblProfileTitle
    //
    this->lblProfileTitle->AutoSize = true;
    this->lblProfileTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblProfileTitle->Location = System::Drawing::Point(15, 15);
    this->lblProfileTitle->Name = L"lblProfileTitle";
    this->lblProfileTitle->Size = System::Drawing::Size(107, 25);
    this->lblProfileTitle->TabIndex = 0;
    this->lblProfileTitle->Text = L"Profil Saya";
    //
    // lblAlamat
    //
    this->lblAlamat->AutoSize = true;
    this->lblAlamat->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
    this->lblAlamat->Location = System::Drawing::Point(15, 60);
    this->lblAlamat->Name = L"lblAlamat";
    this->lblAlamat->Size = System::Drawing::Size(138, 20);
    this->lblAlamat->TabIndex = 1;
    this->lblAlamat->Text = L"Alamat Pengiriman:";
    //
    // txtAlamat
    //
    this->txtAlamat->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
    this->txtAlamat->Location = System::Drawing::Point(15, 85);
    this->txtAlamat->Multiline = true;
    this->txtAlamat->Name = L"txtAlamat";
    this->txtAlamat->Size = System::Drawing::Size(372, 80);
    this->txtAlamat->TabIndex = 2;
    //
    // btnSaveAlamat
    //
    this->btnSaveAlamat->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnSaveAlamat->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnSaveAlamat->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
    this->btnSaveAlamat->ForeColor = System::Drawing::Color::White;
    this->btnSaveAlamat->Location = System::Drawing::Point(15, 201);
    this->btnSaveAlamat->Name = L"btnSaveAlamat";
    this->btnSaveAlamat->Size = System::Drawing::Size(150, 35);
    this->btnSaveAlamat->TabIndex = 3;
    this->btnSaveAlamat->Text = L"Simpan Alamat";
    this->btnSaveAlamat->UseVisualStyleBackColor = false;
    this->btnSaveAlamat->Click +=
        gcnew System::EventHandler(this, &customerForm::btnSaveAlamat_Click);
    //
    // lblAlamatInfo
    //
    this->lblAlamatInfo->AutoSize = true;
    this->lblAlamatInfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
    this->lblAlamatInfo->ForeColor = System::Drawing::Color::Gray;
    this->lblAlamatInfo->Location = System::Drawing::Point(17, 180);
    this->lblAlamatInfo->Name = L"lblAlamatInfo";
    this->lblAlamatInfo->Size = System::Drawing::Size(372, 15);
    this->lblAlamatInfo->TabIndex = 4;
    this->lblAlamatInfo->Text =
        L"Alamat ini akan digunakan untuk pengiriman produk yang Anda beli.";
    //
    // btnLogout
    //
    this->btnLogout->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(220)),
        static_cast<System::Int32>(static_cast<System::Byte>(53)),
        static_cast<System::Int32>(static_cast<System::Byte>(69)));
    this->btnLogout->FlatAppearance->BorderSize = 0;
    this->btnLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->btnLogout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnLogout->ForeColor = System::Drawing::Color::White;
    this->btnLogout->Location = System::Drawing::Point(778, 499);
    this->btnLogout->Name = L"btnLogout";
    this->btnLogout->Size = System::Drawing::Size(90, 30);
    this->btnLogout->TabIndex = 1;
    this->btnLogout->Text = L"Logout";
    this->btnLogout->UseVisualStyleBackColor = false;
    this->btnLogout->Click +=
        gcnew System::EventHandler(this, &customerForm::btnLogout_Click);
    //
    // customerForm
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
    this->Name = L"customerForm";
    this->StartPosition =
        System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Customer Dashboard - E-Commerce";
    this->Load +=
        gcnew System::EventHandler(this, &customerForm::customerForm_Load);
    this->tabControl->ResumeLayout(false);
    this->tabCatalog->ResumeLayout(false);
    this->tabCatalog->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvProducts))
        ->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->nudQuantity))
        ->EndInit();
    this->tabCart->ResumeLayout(false);
    this->tabCart->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvCart))
        ->EndInit();
    this->tabHistory->ResumeLayout(false);
    this->tabHistory->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvHistory))
        ->EndInit();
    this->tabProfile->ResumeLayout(false);
    this->tabProfile->PerformLayout();
    this->ResumeLayout(false);
  }
#pragma endregion

  // ========== Event Handlers (implementations in customerForm.cpp) ==========
private:
  System::Void customerForm_Load(System::Object ^ sender,
                                 System::EventArgs ^ e);
  void LoadCatalog();
  void LoadHistory();
  void LoadSaldo();
  void LoadProfile();
  System::Void btnRefreshCatalog_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnAddToCart_Click(System::Object ^ sender,
                                  System::EventArgs ^ e);
  System::Void btnRemoveFromCart_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnCheckout_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  void UpdateCartTotal();
  System::Void btnRefreshHistory_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnTopUp_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnSaveAlamat_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
};
} // namespace ECommerce
