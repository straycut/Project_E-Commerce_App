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

private:
  System::Windows::Forms::Label ^ label1;
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
    cartTable->Columns->Add("MerchantID", Int32::typeid);
    cartTable->Columns->Add("Toko", String::typeid);
  }

private:
  // Summary panel controls
  System::Windows::Forms::Panel ^ panelSummary;
  System::Windows::Forms::Label ^ lblSummaryTitle;
  System::Windows::Forms::Label ^ lblSubtotal;
  System::Windows::Forms::Label ^ lblOngkir;
  System::Windows::Forms::Label ^ lblGrandTotal;
  System::Windows::Forms::Label ^ lblAlamatCheckout;
  System::Windows::Forms::TextBox ^ txtAlamatCheckout;
  System::Windows::Forms::RadioButton ^ rbRegular;
  System::Windows::Forms::RadioButton ^ rbExpress;
  System::Windows::Forms::Label ^ lblPilihKurir;
  System::Windows::Forms::ComboBox ^ cmbExpressCourier;
  System::Windows::Forms::Label ^ lblSaldoCheckout;

public:
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
    cartTable->Columns->Add("MerchantID", Int32::typeid);
    cartTable->Columns->Add("Toko", String::typeid);
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
  System::Windows::Forms::TextBox ^ txtSearch;

private:
  System::Windows::Forms::Label ^ lblSearch;

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

private:
  System::Windows::Forms::NumericUpDown ^ nudCartQuantity;

private:
  System::Windows::Forms::Button ^ btnUpdateQuantity;

private:
  System::Windows::Forms::Label ^ lblEditQuantity;

  // History
private:
  System::Windows::Forms::Label ^ lblHistoryTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvHistory;

private:
  System::Windows::Forms::Button ^ btnRefreshHistory;

private:
  System::Windows::Forms::Button ^ btnConfirmReceived;

private:
  System::Windows::Forms::Button ^ btnCancelOrder;

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
    this->lblSearch = (gcnew System::Windows::Forms::Label());
    this->txtSearch = (gcnew System::Windows::Forms::TextBox());
    this->dgvProducts = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshCatalog = (gcnew System::Windows::Forms::Button());
    this->lblQuantity = (gcnew System::Windows::Forms::Label());
    this->nudQuantity = (gcnew System::Windows::Forms::NumericUpDown());
    this->btnAddToCart = (gcnew System::Windows::Forms::Button());
    this->lblSaldoInfo = (gcnew System::Windows::Forms::Label());
    this->tabCart = (gcnew System::Windows::Forms::TabPage());
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->lblCartTitle = (gcnew System::Windows::Forms::Label());
    this->dgvCart = (gcnew System::Windows::Forms::DataGridView());
    this->btnRemoveFromCart = (gcnew System::Windows::Forms::Button());
    this->btnCheckout = (gcnew System::Windows::Forms::Button());
    this->lblCartTotal = (gcnew System::Windows::Forms::Label());
    this->lblEditQuantity = (gcnew System::Windows::Forms::Label());
    this->nudCartQuantity = (gcnew System::Windows::Forms::NumericUpDown());
    this->btnUpdateQuantity = (gcnew System::Windows::Forms::Button());
    this->panelSummary = (gcnew System::Windows::Forms::Panel());
    this->lblSummaryTitle = (gcnew System::Windows::Forms::Label());
    this->lblSubtotal = (gcnew System::Windows::Forms::Label());
    this->lblOngkir = (gcnew System::Windows::Forms::Label());
    this->lblGrandTotal = (gcnew System::Windows::Forms::Label());
    this->lblAlamatCheckout = (gcnew System::Windows::Forms::Label());
    this->txtAlamatCheckout = (gcnew System::Windows::Forms::TextBox());
    this->rbRegular = (gcnew System::Windows::Forms::RadioButton());
    this->rbExpress = (gcnew System::Windows::Forms::RadioButton());
    this->lblPilihKurir = (gcnew System::Windows::Forms::Label());
    this->cmbExpressCourier = (gcnew System::Windows::Forms::ComboBox());
    this->lblSaldoCheckout = (gcnew System::Windows::Forms::Label());
    this->tabHistory = (gcnew System::Windows::Forms::TabPage());
    this->lblHistoryTitle = (gcnew System::Windows::Forms::Label());
    this->dgvHistory = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshHistory = (gcnew System::Windows::Forms::Button());
    this->btnConfirmReceived = (gcnew System::Windows::Forms::Button());
    this->btnCancelOrder = (gcnew System::Windows::Forms::Button());
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
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->nudCartQuantity))
        ->BeginInit();
    this->panelSummary->SuspendLayout();
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
    this->tabControl->SelectedIndexChanged += gcnew System::EventHandler(
        this, &customerForm::tabControl_SelectedIndexChanged);
    //
    // tabCatalog
    //
    this->tabCatalog->Controls->Add(this->lblCatalogTitle);
    this->tabCatalog->Controls->Add(this->lblSearch);
    this->tabCatalog->Controls->Add(this->txtSearch);
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
    // lblSearch
    //
    this->lblSearch->AutoSize = true;
    this->lblSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
    this->lblSearch->Location = System::Drawing::Point(200, 18);
    this->lblSearch->Name = L"lblSearch";
    this->lblSearch->Size = System::Drawing::Size(72, 15);
    this->lblSearch->TabIndex = 10;
    this->lblSearch->Text = L"Cari Produk:";
    //
    // txtSearch
    //
    this->txtSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    this->txtSearch->Location = System::Drawing::Point(285, 15);
    this->txtSearch->Name = L"txtSearch";
    this->txtSearch->Size = System::Drawing::Size(250, 25);
    this->txtSearch->TabIndex = 11;
    this->txtSearch->TextChanged +=
        gcnew System::EventHandler(this, &customerForm::txtSearch_TextChanged);
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
    this->btnRefreshCatalog->Location = System::Drawing::Point(15, 410);
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
    this->lblQuantity->Location = System::Drawing::Point(551, 419);
    this->lblQuantity->Name = L"lblQuantity";
    this->lblQuantity->Size = System::Drawing::Size(43, 13);
    this->lblQuantity->TabIndex = 3;
    this->lblQuantity->Text = L"Jumlah:";
    //
    // nudQuantity
    //
    this->nudQuantity->Location = System::Drawing::Point(606, 416);
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
    this->btnAddToCart->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnAddToCart->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnAddToCart->FlatAppearance->BorderSize = 0;
    this->btnAddToCart->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnAddToCart->ForeColor = System::Drawing::Color::White;
    this->btnAddToCart->Location = System::Drawing::Point(681, 411);
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
    this->lblSaldoInfo->ForeColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(46)),
        static_cast<System::Int32>(static_cast<System::Byte>(125)),
        static_cast<System::Int32>(static_cast<System::Byte>(50)));
    this->lblSaldoInfo->Location = System::Drawing::Point(550, 15);
    this->lblSaldoInfo->Name = L"lblSaldoInfo";
    this->lblSaldoInfo->Size = System::Drawing::Size(94, 21);
    this->lblSaldoInfo->TabIndex = 4;
    this->lblSaldoInfo->Text = L"Saldo: Rp 0";
    //
    // tabCart
    //
    this->tabCart->Controls->Add(this->label1);
    this->tabCart->Controls->Add(this->lblCartTitle);
    this->tabCart->Controls->Add(this->dgvCart);
    this->tabCart->Controls->Add(this->btnRemoveFromCart);
    this->tabCart->Controls->Add(this->lblCartTotal);
    this->tabCart->Controls->Add(this->lblEditQuantity);
    this->tabCart->Controls->Add(this->nudCartQuantity);
    this->tabCart->Controls->Add(this->btnUpdateQuantity);
    this->tabCart->Controls->Add(this->panelSummary);
    this->tabCart->Location = System::Drawing::Point(4, 22);
    this->tabCart->Name = L"tabCart";
    this->tabCart->Size = System::Drawing::Size(852, 454);
    this->tabCart->TabIndex = 5;
    this->tabCart->Text = L"Checkout";
    this->tabCart->UseVisualStyleBackColor = true;
    //
    // label1
    //
    this->label1->AutoSize = true;
    this->label1->Location = System::Drawing::Point(151, 427);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(0, 13);
    this->label1->TabIndex = 8;
    this->label1->Visible = false;
    //
    // lblCartTitle
    //
    this->lblCartTitle->AutoSize = true;
    this->lblCartTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblCartTitle->Location = System::Drawing::Point(15, 10);
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
    this->dgvCart->Location = System::Drawing::Point(15, 40);
    this->dgvCart->MultiSelect = false;
    this->dgvCart->Name = L"dgvCart";
    this->dgvCart->ReadOnly = true;
    this->dgvCart->SelectionMode =
        System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->dgvCart->Size = System::Drawing::Size(455, 340);
    this->dgvCart->TabIndex = 1;
    //
    // btnRemoveFromCart
    //
    this->btnRemoveFromCart->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(211)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)));
    this->btnRemoveFromCart->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnRemoveFromCart->FlatAppearance->BorderSize = 0;
    this->btnRemoveFromCart->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnRemoveFromCart->ForeColor = System::Drawing::Color::White;
    this->btnRemoveFromCart->Location = System::Drawing::Point(370, 388);
    this->btnRemoveFromCart->Name = L"btnRemoveFromCart";
    this->btnRemoveFromCart->Size = System::Drawing::Size(100, 28);
    this->btnRemoveFromCart->TabIndex = 2;
    this->btnRemoveFromCart->Text = L"Hapus Item";
    this->btnRemoveFromCart->UseVisualStyleBackColor = false;
    this->btnRemoveFromCart->Click += gcnew System::EventHandler(
        this, &customerForm::btnRemoveFromCart_Click);
    //
    // btnCheckout
    //
    this->btnCheckout->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnCheckout->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnCheckout->FlatAppearance->BorderSize = 0;
    this->btnCheckout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
    this->btnCheckout->ForeColor = System::Drawing::Color::White;
    this->btnCheckout->Location = System::Drawing::Point(12, 386);
    this->btnCheckout->Name = L"btnCheckout";
    this->btnCheckout->Size = System::Drawing::Size(330, 39);
    this->btnCheckout->TabIndex = 3;
    this->btnCheckout->Text = L"CHECKOUT";
    this->btnCheckout->UseVisualStyleBackColor = false;
    this->btnCheckout->Click +=
        gcnew System::EventHandler(this, &customerForm::btnCheckout_Click);
    //
    // lblCartTotal
    //
    this->lblCartTotal->AutoSize = true;
    this->lblCartTotal->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->lblCartTotal->Location = System::Drawing::Point(15, 455);
    this->lblCartTotal->Name = L"lblCartTotal";
    this->lblCartTotal->Size = System::Drawing::Size(89, 21);
    this->lblCartTotal->TabIndex = 4;
    this->lblCartTotal->Text = L"Total: Rp 0";
    this->lblCartTotal->Visible = false;
    //
    // lblEditQuantity
    //
    this->lblEditQuantity->AutoSize = true;
    this->lblEditQuantity->Location = System::Drawing::Point(15, 393);
    this->lblEditQuantity->Name = L"lblEditQuantity";
    this->lblEditQuantity->Size = System::Drawing::Size(43, 13);
    this->lblEditQuantity->TabIndex = 5;
    this->lblEditQuantity->Text = L"Jumlah:";
    //
    // nudCartQuantity
    //
    this->nudCartQuantity->Location = System::Drawing::Point(68, 390);
    this->nudCartQuantity->Minimum =
        System::Decimal(gcnew cli::array<System::Int32>(4){1, 0, 0, 0});
    this->nudCartQuantity->Name = L"nudCartQuantity";
    this->nudCartQuantity->Size = System::Drawing::Size(55, 20);
    this->nudCartQuantity->TabIndex = 6;
    this->nudCartQuantity->Value =
        System::Decimal(gcnew cli::array<System::Int32>(4){1, 0, 0, 0});
    //
    // btnUpdateQuantity
    //
    this->btnUpdateQuantity->BackColor = System::Drawing::Color::White;
    this->btnUpdateQuantity->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnUpdateQuantity->FlatAppearance->BorderColor =
        System::Drawing::Color::FromArgb(
            static_cast<System::Int32>(static_cast<System::Byte>(46)),
            static_cast<System::Int32>(static_cast<System::Byte>(125)),
            static_cast<System::Int32>(static_cast<System::Byte>(50)));
    this->btnUpdateQuantity->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnUpdateQuantity->ForeColor = System::Drawing::Color::MediumSeaGreen;
    this->btnUpdateQuantity->Location = System::Drawing::Point(130, 386);
    this->btnUpdateQuantity->Name = L"btnUpdateQuantity";
    this->btnUpdateQuantity->Size = System::Drawing::Size(95, 28);
    this->btnUpdateQuantity->TabIndex = 7;
    this->btnUpdateQuantity->Text = L"Ubah Jumlah";
    this->btnUpdateQuantity->UseVisualStyleBackColor = false;
    this->btnUpdateQuantity->Click += gcnew System::EventHandler(
        this, &customerForm::btnUpdateQuantity_Click);
    //
    // panelSummary
    //
    this->panelSummary->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(245)),
        static_cast<System::Int32>(static_cast<System::Byte>(247)),
        static_cast<System::Int32>(static_cast<System::Byte>(250)));
    this->panelSummary->BorderStyle =
        System::Windows::Forms::BorderStyle::FixedSingle;
    this->panelSummary->Controls->Add(this->lblSummaryTitle);
    this->panelSummary->Controls->Add(this->lblSubtotal);
    this->panelSummary->Controls->Add(this->lblOngkir);
    this->panelSummary->Controls->Add(this->lblGrandTotal);
    this->panelSummary->Controls->Add(this->btnCheckout);
    this->panelSummary->Controls->Add(this->lblAlamatCheckout);
    this->panelSummary->Controls->Add(this->txtAlamatCheckout);
    this->panelSummary->Controls->Add(this->rbRegular);
    this->panelSummary->Controls->Add(this->rbExpress);
    this->panelSummary->Controls->Add(this->lblPilihKurir);
    this->panelSummary->Controls->Add(this->cmbExpressCourier);
    this->panelSummary->Controls->Add(this->lblSaldoCheckout);
    this->panelSummary->Location = System::Drawing::Point(480, 10);
    this->panelSummary->Name = L"panelSummary";
    this->panelSummary->Size = System::Drawing::Size(360, 440);
    this->panelSummary->TabIndex = 9;
    //
    // lblSummaryTitle
    //
    this->lblSummaryTitle->AutoSize = true;
    this->lblSummaryTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
    this->lblSummaryTitle->Location = System::Drawing::Point(12, 10);
    this->lblSummaryTitle->Name = L"lblSummaryTitle";
    this->lblSummaryTitle->Size = System::Drawing::Size(157, 21);
    this->lblSummaryTitle->TabIndex = 0;
    this->lblSummaryTitle->Text = L"Ringkasan Pesanan";
    //
    // lblSubtotal
    //
    this->lblSubtotal->AutoSize = true;
    this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    this->lblSubtotal->Location = System::Drawing::Point(12, 42);
    this->lblSubtotal->Name = L"lblSubtotal";
    this->lblSubtotal->Size = System::Drawing::Size(95, 19);
    this->lblSubtotal->TabIndex = 1;
    this->lblSubtotal->Text = L"Subtotal: Rp 0";
    //
    // lblOngkir
    //
    this->lblOngkir->AutoSize = true;
    this->lblOngkir->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    this->lblOngkir->Location = System::Drawing::Point(12, 65);
    this->lblOngkir->Name = L"lblOngkir";
    this->lblOngkir->Size = System::Drawing::Size(86, 19);
    this->lblOngkir->TabIndex = 2;
    this->lblOngkir->Text = L"Ongkir: Rp 0";
    //
    // lblGrandTotal
    //
    this->lblGrandTotal->AutoSize = true;
    this->lblGrandTotal->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 13, System::Drawing::FontStyle::Bold));
    this->lblGrandTotal->ForeColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(46)),
        static_cast<System::Int32>(static_cast<System::Byte>(125)),
        static_cast<System::Int32>(static_cast<System::Byte>(50)));
    this->lblGrandTotal->Location = System::Drawing::Point(12, 92);
    this->lblGrandTotal->Name = L"lblGrandTotal";
    this->lblGrandTotal->Size = System::Drawing::Size(159, 25);
    this->lblGrandTotal->TabIndex = 3;
    this->lblGrandTotal->Text = L"Grand Total: Rp 0";
    //
    // lblAlamatCheckout
    //
    this->lblAlamatCheckout->AutoSize = true;
    this->lblAlamatCheckout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->lblAlamatCheckout->Location = System::Drawing::Point(12, 130);
    this->lblAlamatCheckout->Name = L"lblAlamatCheckout";
    this->lblAlamatCheckout->Size = System::Drawing::Size(115, 15);
    this->lblAlamatCheckout->TabIndex = 4;
    this->lblAlamatCheckout->Text = L"Alamat Pengiriman:";
    //
    // txtAlamatCheckout
    //
    this->txtAlamatCheckout->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 9));
    this->txtAlamatCheckout->Location = System::Drawing::Point(12, 150);
    this->txtAlamatCheckout->Multiline = true;
    this->txtAlamatCheckout->Name = L"txtAlamatCheckout";
    this->txtAlamatCheckout->Size = System::Drawing::Size(330, 50);
    this->txtAlamatCheckout->TabIndex = 5;
    //
    // rbRegular
    //
    this->rbRegular->AutoSize = true;
    this->rbRegular->Checked = true;
    this->rbRegular->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->rbRegular->Location = System::Drawing::Point(12, 215);
    this->rbRegular->Name = L"rbRegular";
    this->rbRegular->Size = System::Drawing::Size(166, 19);
    this->rbRegular->TabIndex = 6;
    this->rbRegular->TabStop = true;
    this->rbRegular->Text = L"Regular (Rp 10.000/toko)";
    this->rbRegular->CheckedChanged += gcnew System::EventHandler(
        this, &customerForm::rbExpress_CheckedChanged);
    //
    // rbExpress
    //
    this->rbExpress->AutoSize = true;
    this->rbExpress->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->rbExpress->Location = System::Drawing::Point(12, 240);
    this->rbExpress->Name = L"rbExpress";
    this->rbExpress->Size = System::Drawing::Size(165, 19);
    this->rbExpress->TabIndex = 7;
    this->rbExpress->Text = L"Express (Rp 20.000/toko)";
    this->rbExpress->CheckedChanged += gcnew System::EventHandler(
        this, &customerForm::rbExpress_CheckedChanged);
    //
    // lblPilihKurir
    //
    this->lblPilihKurir->AutoSize = true;
    this->lblPilihKurir->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
    this->lblPilihKurir->Location = System::Drawing::Point(12, 270);
    this->lblPilihKurir->Name = L"lblPilihKurir";
    this->lblPilihKurir->Size = System::Drawing::Size(102, 15);
    this->lblPilihKurir->TabIndex = 8;
    this->lblPilihKurir->Text = L"Pilih Kurir Express:";
    this->lblPilihKurir->Visible = false;
    //
    // cmbExpressCourier
    //
    this->cmbExpressCourier->DropDownStyle =
        System::Windows::Forms::ComboBoxStyle::DropDownList;
    this->cmbExpressCourier->Font =
        (gcnew System::Drawing::Font(L"Segoe UI", 9));
    this->cmbExpressCourier->Location = System::Drawing::Point(12, 290);
    this->cmbExpressCourier->Name = L"cmbExpressCourier";
    this->cmbExpressCourier->Size = System::Drawing::Size(330, 23);
    this->cmbExpressCourier->TabIndex = 9;
    this->cmbExpressCourier->Visible = false;
    //
    // lblSaldoCheckout
    //
    this->lblSaldoCheckout->AutoSize = true;
    this->lblSaldoCheckout->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
    this->lblSaldoCheckout->ForeColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(46)),
        static_cast<System::Int32>(static_cast<System::Byte>(125)),
        static_cast<System::Int32>(static_cast<System::Byte>(50)));
    this->lblSaldoCheckout->Location = System::Drawing::Point(13, 363);
    this->lblSaldoCheckout->Name = L"lblSaldoCheckout";
    this->lblSaldoCheckout->Size = System::Drawing::Size(87, 20);
    this->lblSaldoCheckout->TabIndex = 10;
    this->lblSaldoCheckout->Text = L"Saldo: Rp 0";
    //
    // tabHistory
    //
    this->tabHistory->Controls->Add(this->lblHistoryTitle);
    this->tabHistory->Controls->Add(this->dgvHistory);
    this->tabHistory->Controls->Add(this->btnRefreshHistory);
    this->tabHistory->Controls->Add(this->btnConfirmReceived);
    this->tabHistory->Controls->Add(this->btnCancelOrder);
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
    this->btnRefreshHistory->Location = System::Drawing::Point(15, 411);
    this->btnRefreshHistory->Name = L"btnRefreshHistory";
    this->btnRefreshHistory->Size = System::Drawing::Size(100, 30);
    this->btnRefreshHistory->TabIndex = 2;
    this->btnRefreshHistory->Text = L"Refresh";
    this->btnRefreshHistory->UseVisualStyleBackColor = true;
    this->btnRefreshHistory->Click += gcnew System::EventHandler(
        this, &customerForm::btnRefreshHistory_Click);
    //
    // btnConfirmReceived
    //
    this->btnConfirmReceived->BackColor =
        System::Drawing::Color::MediumSeaGreen;
    this->btnConfirmReceived->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnConfirmReceived->FlatAppearance->BorderSize = 0;
    this->btnConfirmReceived->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnConfirmReceived->ForeColor = System::Drawing::Color::White;
    this->btnConfirmReceived->Location = System::Drawing::Point(130, 411);
    this->btnConfirmReceived->Name = L"btnConfirmReceived";
    this->btnConfirmReceived->Size = System::Drawing::Size(139, 30);
    this->btnConfirmReceived->TabIndex = 12;
    this->btnConfirmReceived->Text = L"Konfirmasi Diterima";
    this->btnConfirmReceived->UseVisualStyleBackColor = false;
    this->btnConfirmReceived->Click += gcnew System::EventHandler(
        this, &customerForm::btnConfirmReceived_Click);
    //
    // btnCancelOrder
    //
    this->btnCancelOrder->BackColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(211)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)));
    this->btnCancelOrder->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnCancelOrder->FlatAppearance->BorderSize = 0;
    this->btnCancelOrder->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnCancelOrder->ForeColor = System::Drawing::Color::White;
    this->btnCancelOrder->Location = System::Drawing::Point(284, 411);
    this->btnCancelOrder->Name = L"btnCancelOrder";
    this->btnCancelOrder->Size = System::Drawing::Size(116, 30);
    this->btnCancelOrder->TabIndex = 13;
    this->btnCancelOrder->Text = L"Batalkan Pesanan";
    this->btnCancelOrder->UseVisualStyleBackColor = false;
    this->btnCancelOrder->Click +=
        gcnew System::EventHandler(this, &customerForm::btnCancelOrder_Click);
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
    this->lblCurrentSaldo->ForeColor = System::Drawing::Color::FromArgb(
        static_cast<System::Int32>(static_cast<System::Byte>(46)),
        static_cast<System::Int32>(static_cast<System::Byte>(125)),
        static_cast<System::Int32>(static_cast<System::Byte>(50)));
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
    this->btnTopUp->BackColor = System::Drawing::Color::MediumSeaGreen;
    this->btnTopUp->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnTopUp->FlatAppearance->BorderSize = 0;
    this->btnTopUp->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
    this->btnTopUp->ForeColor = System::Drawing::Color::White;
    this->btnTopUp->Location = System::Drawing::Point(487, 189);
    this->btnTopUp->Name = L"btnTopUp";
    this->btnTopUp->Size = System::Drawing::Size(200, 35);
    this->btnTopUp->TabIndex = 9;
    this->btnTopUp->Text = L"Top Up Saldo";
    this->btnTopUp->UseVisualStyleBackColor = false;
    this->btnTopUp->Click +=
        gcnew System::EventHandler(this, &customerForm::btnTopUp_Click);
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
    this->btnSaveAlamat->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnSaveAlamat->FlatAppearance->BorderSize = 0;
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
        static_cast<System::Int32>(static_cast<System::Byte>(211)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)),
        static_cast<System::Int32>(static_cast<System::Byte>(47)));
    this->btnLogout->Cursor = System::Windows::Forms::Cursors::Hand;
    this->btnLogout->FlatAppearance->BorderSize = 0;
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
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->nudCartQuantity))
        ->EndInit();
    this->panelSummary->ResumeLayout(false);
    this->panelSummary->PerformLayout();
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
  System::Void tabControl_SelectedIndexChanged(System::Object ^ sender,
                                               System::EventArgs ^ e);
  System::Void customerForm_Load(System::Object ^ sender,
                                 System::EventArgs ^ e);
  void LoadCatalog();
  void LoadHistory();
  void LoadSaldo();
  void LoadProfile();
  void FilterProducts(String ^ keyword);
  System::Void txtSearch_TextChanged(System::Object ^ sender,
                                     System::EventArgs ^ e);
  System::Void btnRefreshCatalog_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnAddToCart_Click(System::Object ^ sender,
                                  System::EventArgs ^ e);
  System::Void btnRemoveFromCart_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnCheckout_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  void UpdateCartTotal();
  System::Void btnUpdateQuantity_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnRefreshHistory_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnConfirmReceived_Click(System::Object ^ sender,
                                        System::EventArgs ^ e);
  System::Void btnCancelOrder_Click(System::Object ^ sender,
                                    System::EventArgs ^ e);
  System::Void btnTopUp_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnSaveAlamat_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
  void LoadExpressCouriers();
  System::Void rbExpress_CheckedChanged(System::Object ^ sender,
                                        System::EventArgs ^ e);
  // Refund request
  System::Void btnRequestRefund_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  // Rating
  System::Void btnGiveRating_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  // Tracking
  System::Void btnTrackOrder_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);

private:
  System::Windows::Forms::Button ^ btnRequestRefund;
  System::Windows::Forms::Button ^ btnGiveRating;
  System::Windows::Forms::Button ^ btnTrackOrder;
};
} // namespace ECommerce
