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
/// Merchant Dashboard - Manage products and view sales
/// </summary>
public
ref class merchantForm : public System::Windows::Forms::Form {
public:
  int currentUserID;
  String ^ currentUsername;

  merchantForm(void) {
    InitializeComponent();
    currentUserID = 0;
    currentUsername = "";
  }

  merchantForm(int userID, String ^ username) {
    InitializeComponent();
    currentUserID = userID;
    currentUsername = username;
  }

protected:
  ~merchantForm() {
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
  System::Windows::Forms::TabPage ^ tabProducts;

private:
  System::Windows::Forms::TabPage ^ tabSales;

private:
  System::Windows::Forms::TabPage ^ tabProfile;

  // Dashboard controls
private:
  System::Windows::Forms::Label ^ lblTitle;

private:
  System::Windows::Forms::Label ^ lblTotalProducts;

private:
  System::Windows::Forms::Label ^ lblTotalSales;

private:
  System::Windows::Forms::Label ^ lblTotalIncome;

private:
  System::Windows::Forms::Label ^ lblCurrentBalance;

private:
  System::Windows::Forms::Label ^ lblWithdrawLabel;

private:
  System::Windows::Forms::TextBox ^ txtWithdrawAmount;

private:
  System::Windows::Forms::Button ^ btnWithdraw;

private:
  System::Windows::Forms::Button ^ btnRefreshDashboard;

  // Products controls
private:
  System::Windows::Forms::Label ^ lblProductsTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvProducts;

private:
  System::Windows::Forms::Button ^ btnRefreshProducts;

private:
  System::Windows::Forms::Button ^ btnAddProduct;

private:
  System::Windows::Forms::Button ^ btnEditProduct;

private:
  System::Windows::Forms::Button ^ btnDeleteProduct;

  // Add/Edit Product panel
private:
  System::Windows::Forms::Panel ^ panelProduct;

private:
  System::Windows::Forms::Label ^ lblNamaProduk;

private:
  System::Windows::Forms::TextBox ^ txtNamaProduk;

private:
  System::Windows::Forms::Label ^ lblHarga;

private:
  System::Windows::Forms::TextBox ^ txtHarga;

private:
  System::Windows::Forms::Label ^ lblKomisi;

private:
  System::Windows::Forms::TextBox ^ txtKomisi;

private:
  System::Windows::Forms::Label ^ lblStok;

private:
  System::Windows::Forms::TextBox ^ txtStok;

private:
  System::Windows::Forms::Button ^ btnSaveProduct;

private:
  System::Windows::Forms::Button ^ btnCancelProduct;

private:
  System::Windows::Forms::Button ^ btnAddStock;

  // Sales controls
private:
  System::Windows::Forms::Label ^ lblSalesTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvSales;

private:
  System::Windows::Forms::Button ^ btnRefreshSales;

  // Profile/Location Controls
private:
  System::Windows::Forms::Label ^ lblProfileTitle;

private:
  System::Windows::Forms::Label ^ lblAlamatToko;

private:
  System::Windows::Forms::TextBox ^ txtAlamatToko;

private:
  System::Windows::Forms::Button ^ btnSaveAlamat;

private:
  System::Windows::Forms::Label ^ lblAlamatInfo;

  // Logout
private:
  System::Windows::Forms::Button ^ btnLogout;

private:
  System::ComponentModel::Container ^ components;

private:
  bool isEditMode;

private:
  int editProductID;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
      this->tabControl = (gcnew System::Windows::Forms::TabControl());
      this->tabDashboard = (gcnew System::Windows::Forms::TabPage());
      this->lblTitle = (gcnew System::Windows::Forms::Label());
      this->lblTotalProducts = (gcnew System::Windows::Forms::Label());
      this->lblTotalSales = (gcnew System::Windows::Forms::Label());
      this->lblTotalIncome = (gcnew System::Windows::Forms::Label());
      this->lblCurrentBalance = (gcnew System::Windows::Forms::Label());
      this->lblWithdrawLabel = (gcnew System::Windows::Forms::Label());
      this->txtWithdrawAmount = (gcnew System::Windows::Forms::TextBox());
      this->btnWithdraw = (gcnew System::Windows::Forms::Button());
      this->btnRefreshDashboard = (gcnew System::Windows::Forms::Button());
      this->tabProducts = (gcnew System::Windows::Forms::TabPage());
      this->lblProductsTitle = (gcnew System::Windows::Forms::Label());
      this->dgvProducts = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshProducts = (gcnew System::Windows::Forms::Button());
      this->btnAddProduct = (gcnew System::Windows::Forms::Button());
      this->btnEditProduct = (gcnew System::Windows::Forms::Button());
      this->btnDeleteProduct = (gcnew System::Windows::Forms::Button());
      this->btnAddStock = (gcnew System::Windows::Forms::Button());
      this->panelProduct = (gcnew System::Windows::Forms::Panel());
      this->lblNamaProduk = (gcnew System::Windows::Forms::Label());
      this->txtNamaProduk = (gcnew System::Windows::Forms::TextBox());
      this->lblHarga = (gcnew System::Windows::Forms::Label());
      this->txtHarga = (gcnew System::Windows::Forms::TextBox());
      this->lblKomisi = (gcnew System::Windows::Forms::Label());
      this->txtKomisi = (gcnew System::Windows::Forms::TextBox());
      this->lblStok = (gcnew System::Windows::Forms::Label());
      this->txtStok = (gcnew System::Windows::Forms::TextBox());
      this->btnSaveProduct = (gcnew System::Windows::Forms::Button());
      this->btnCancelProduct = (gcnew System::Windows::Forms::Button());
      this->tabSales = (gcnew System::Windows::Forms::TabPage());
      this->lblSalesTitle = (gcnew System::Windows::Forms::Label());
      this->dgvSales = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshSales = (gcnew System::Windows::Forms::Button());
      this->tabProfile = (gcnew System::Windows::Forms::TabPage());
      this->lblProfileTitle = (gcnew System::Windows::Forms::Label());
      this->lblAlamatToko = (gcnew System::Windows::Forms::Label());
      this->txtAlamatToko = (gcnew System::Windows::Forms::TextBox());
      this->btnSaveAlamat = (gcnew System::Windows::Forms::Button());
      this->lblAlamatInfo = (gcnew System::Windows::Forms::Label());
      this->btnLogout = (gcnew System::Windows::Forms::Button());
      this->tabControl->SuspendLayout();
      this->tabDashboard->SuspendLayout();
      this->tabProducts->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvProducts))->BeginInit();
      this->panelProduct->SuspendLayout();
      this->tabSales->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSales))->BeginInit();
      this->tabProfile->SuspendLayout();
      this->SuspendLayout();
      // 
      // tabControl
      // 
      this->tabControl->Controls->Add(this->tabDashboard);
      this->tabControl->Controls->Add(this->tabProducts);
      this->tabControl->Controls->Add(this->tabSales);
      this->tabControl->Controls->Add(this->tabProfile);
      this->tabControl->Location = System::Drawing::Point(12, 12);
      this->tabControl->Name = L"tabControl";
      this->tabControl->SelectedIndex = 0;
      this->tabControl->Size = System::Drawing::Size(860, 480);
      this->tabControl->TabIndex = 0;
      // 
      // tabDashboard
      // 
      this->tabDashboard->Controls->Add(this->lblTitle);
      this->tabDashboard->Controls->Add(this->lblTotalProducts);
      this->tabDashboard->Controls->Add(this->lblTotalSales);
      this->tabDashboard->Controls->Add(this->lblTotalIncome);
      this->tabDashboard->Controls->Add(this->lblCurrentBalance);
      this->tabDashboard->Controls->Add(this->lblWithdrawLabel);
      this->tabDashboard->Controls->Add(this->txtWithdrawAmount);
      this->tabDashboard->Controls->Add(this->btnWithdraw);
      this->tabDashboard->Controls->Add(this->btnRefreshDashboard);
      this->tabDashboard->Location = System::Drawing::Point(4, 22);
      this->tabDashboard->Name = L"tabDashboard";
      this->tabDashboard->Padding = System::Windows::Forms::Padding(3);
      this->tabDashboard->Size = System::Drawing::Size(852, 454);
      this->tabDashboard->TabIndex = 0;
      this->tabDashboard->Text = L"Dashboard";
      this->tabDashboard->UseVisualStyleBackColor = true;
      // 
      // lblTitle
      // 
      this->lblTitle->AutoSize = true;
      this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
      this->lblTitle->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->lblTitle->Location = System::Drawing::Point(20, 20);
      this->lblTitle->Name = L"lblTitle";
      this->lblTitle->Size = System::Drawing::Size(254, 32);
      this->lblTitle->TabIndex = 0;
      this->lblTitle->Text = L"Merchant Dashboard";
      // 
      // lblTotalProducts
      // 
      this->lblTotalProducts->AutoSize = true;
      this->lblTotalProducts->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
      this->lblTotalProducts->Location = System::Drawing::Point(21, 119);
      this->lblTotalProducts->Name = L"lblTotalProducts";
      this->lblTotalProducts->Size = System::Drawing::Size(136, 25);
      this->lblTotalProducts->TabIndex = 1;
      this->lblTotalProducts->Text = L"Total Produk: 0";
      // 
      // lblTotalSales
      // 
      this->lblTotalSales->AutoSize = true;
      this->lblTotalSales->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
      this->lblTotalSales->Location = System::Drawing::Point(21, 145);
      this->lblTotalSales->Name = L"lblTotalSales";
      this->lblTotalSales->Size = System::Drawing::Size(159, 25);
      this->lblTotalSales->TabIndex = 2;
      this->lblTotalSales->Text = L"Total Penjualan: 0";
      // 
      // lblTotalIncome
      // 
      this->lblTotalIncome->AutoSize = true;
      this->lblTotalIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblTotalIncome->ForeColor = System::Drawing::Color::DarkGreen;
      this->lblTotalIncome->Location = System::Drawing::Point(21, 172);
      this->lblTotalIncome->Name = L"lblTotalIncome";
      this->lblTotalIncome->Size = System::Drawing::Size(168, 25);
      this->lblTotalIncome->TabIndex = 3;
      this->lblTotalIncome->Text = L"Pendapatan: Rp 0";
      // 
      // lblCurrentBalance
      // 
      this->lblCurrentBalance->AutoSize = true;
      this->lblCurrentBalance->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblCurrentBalance->ForeColor = System::Drawing::Color::DarkBlue;
      this->lblCurrentBalance->Location = System::Drawing::Point(21, 52);
      this->lblCurrentBalance->Name = L"lblCurrentBalance";
      this->lblCurrentBalance->Size = System::Drawing::Size(112, 25);
      this->lblCurrentBalance->TabIndex = 4;
      this->lblCurrentBalance->Text = L"Saldo: Rp 0";
      // 
      // lblWithdrawLabel
      // 
      this->lblWithdrawLabel->AutoSize = true;
      this->lblWithdrawLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
      this->lblWithdrawLabel->Location = System::Drawing::Point(22, 223);
      this->lblWithdrawLabel->Name = L"lblWithdrawLabel";
      this->lblWithdrawLabel->Size = System::Drawing::Size(88, 21);
      this->lblWithdrawLabel->TabIndex = 5;
      this->lblWithdrawLabel->Text = L"Tarik Saldo:";
      // 
      // txtWithdrawAmount
      // 
      this->txtWithdrawAmount->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->txtWithdrawAmount->Location = System::Drawing::Point(26, 247);
      this->txtWithdrawAmount->Name = L"txtWithdrawAmount";
      this->txtWithdrawAmount->Size = System::Drawing::Size(200, 27);
      this->txtWithdrawAmount->TabIndex = 6;
      // 
      // btnWithdraw
      // 
      this->btnWithdraw->BackColor = System::Drawing::Color::MediumSeaGreen;
      this->btnWithdraw->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
      this->btnWithdraw->ForeColor = System::Drawing::Color::White;
      this->btnWithdraw->Location = System::Drawing::Point(26, 280);
      this->btnWithdraw->Name = L"btnWithdraw";
      this->btnWithdraw->Size = System::Drawing::Size(200, 30);
      this->btnWithdraw->TabIndex = 7;
      this->btnWithdraw->Text = L"Tarik";
      this->btnWithdraw->UseVisualStyleBackColor = false;
      this->btnWithdraw->Click += gcnew System::EventHandler(this, &merchantForm::btnWithdraw_Click);
      // 
      // btnRefreshDashboard
      // 
      this->btnRefreshDashboard->Location = System::Drawing::Point(26, 392);
      this->btnRefreshDashboard->Name = L"btnRefreshDashboard";
      this->btnRefreshDashboard->Size = System::Drawing::Size(120, 30);
      this->btnRefreshDashboard->TabIndex = 8;
      this->btnRefreshDashboard->Text = L"Refresh";
      this->btnRefreshDashboard->UseVisualStyleBackColor = true;
      this->btnRefreshDashboard->Click += gcnew System::EventHandler(this, &merchantForm::btnRefreshDashboard_Click);
      // 
      // tabProducts
      // 
      this->tabProducts->Controls->Add(this->lblProductsTitle);
      this->tabProducts->Controls->Add(this->dgvProducts);
      this->tabProducts->Controls->Add(this->btnRefreshProducts);
      this->tabProducts->Controls->Add(this->btnAddProduct);
      this->tabProducts->Controls->Add(this->btnEditProduct);
      this->tabProducts->Controls->Add(this->btnDeleteProduct);
      this->tabProducts->Controls->Add(this->btnAddStock);
      this->tabProducts->Controls->Add(this->panelProduct);
      this->tabProducts->Location = System::Drawing::Point(4, 22);
      this->tabProducts->Name = L"tabProducts";
      this->tabProducts->Padding = System::Windows::Forms::Padding(3);
      this->tabProducts->Size = System::Drawing::Size(852, 454);
      this->tabProducts->TabIndex = 1;
      this->tabProducts->Text = L"Produk Saya";
      this->tabProducts->UseVisualStyleBackColor = true;
      // 
      // lblProductsTitle
      // 
      this->lblProductsTitle->AutoSize = true;
      this->lblProductsTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblProductsTitle->Location = System::Drawing::Point(15, 15);
      this->lblProductsTitle->Name = L"lblProductsTitle";
      this->lblProductsTitle->Size = System::Drawing::Size(125, 25);
      this->lblProductsTitle->TabIndex = 0;
      this->lblProductsTitle->Text = L"Produk Saya";
      // 
      // dgvProducts
      // 
      this->dgvProducts->AllowUserToAddRows = false;
      this->dgvProducts->AllowUserToDeleteRows = false;
      this->dgvProducts->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvProducts->Location = System::Drawing::Point(15, 50);
      this->dgvProducts->MultiSelect = false;
      this->dgvProducts->Name = L"dgvProducts";
      this->dgvProducts->ReadOnly = true;
      this->dgvProducts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
      this->dgvProducts->Size = System::Drawing::Size(533, 320);
      this->dgvProducts->TabIndex = 1;
      // 
      // btnRefreshProducts
      // 
      this->btnRefreshProducts->Location = System::Drawing::Point(15, 376);
      this->btnRefreshProducts->Name = L"btnRefreshProducts";
      this->btnRefreshProducts->Size = System::Drawing::Size(100, 30);
      this->btnRefreshProducts->TabIndex = 2;
      this->btnRefreshProducts->Text = L"Refresh";
      this->btnRefreshProducts->UseVisualStyleBackColor = true;
      this->btnRefreshProducts->Click += gcnew System::EventHandler(this, &merchantForm::btnRefreshProducts_Click);
      // 
      // btnAddProduct
      // 
      this->btnAddProduct->BackColor = System::Drawing::Color::White;
      this->btnAddProduct->Location = System::Drawing::Point(125, 376);
      this->btnAddProduct->Name = L"btnAddProduct";
      this->btnAddProduct->Size = System::Drawing::Size(100, 30);
      this->btnAddProduct->TabIndex = 3;
      this->btnAddProduct->Text = L"Tambah";
      this->btnAddProduct->UseVisualStyleBackColor = false;
      this->btnAddProduct->Click += gcnew System::EventHandler(this, &merchantForm::btnAddProduct_Click);
      // 
      // btnEditProduct
      // 
      this->btnEditProduct->BackColor = System::Drawing::Color::White;
      this->btnEditProduct->Location = System::Drawing::Point(235, 376);
      this->btnEditProduct->Name = L"btnEditProduct";
      this->btnEditProduct->Size = System::Drawing::Size(100, 30);
      this->btnEditProduct->TabIndex = 4;
      this->btnEditProduct->Text = L"Edit";
      this->btnEditProduct->UseVisualStyleBackColor = false;
      this->btnEditProduct->Click += gcnew System::EventHandler(this, &merchantForm::btnEditProduct_Click);
      // 
      // btnDeleteProduct
      // 
      this->btnDeleteProduct->BackColor = System::Drawing::Color::White;
      this->btnDeleteProduct->Location = System::Drawing::Point(345, 376);
      this->btnDeleteProduct->Name = L"btnDeleteProduct";
      this->btnDeleteProduct->Size = System::Drawing::Size(100, 30);
      this->btnDeleteProduct->TabIndex = 5;
      this->btnDeleteProduct->Text = L"Hapus";
      this->btnDeleteProduct->UseVisualStyleBackColor = false;
      this->btnDeleteProduct->Click += gcnew System::EventHandler(this, &merchantForm::btnDeleteProduct_Click);
      // 
      // btnAddStock
      // 
      this->btnAddStock->BackColor = System::Drawing::Color::MediumSeaGreen;
      this->btnAddStock->ForeColor = System::Drawing::Color::White;
      this->btnAddStock->Location = System::Drawing::Point(15, 412);
      this->btnAddStock->Name = L"btnAddStock";
      this->btnAddStock->Size = System::Drawing::Size(100, 30);
      this->btnAddStock->TabIndex = 8;
      this->btnAddStock->Text = L"+ Stok";
      this->btnAddStock->UseVisualStyleBackColor = false;
      this->btnAddStock->Click += gcnew System::EventHandler(this, &merchantForm::btnAddStock_Click);
      // 
      // panelProduct
      // 
      this->panelProduct->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panelProduct->Controls->Add(this->lblNamaProduk);
      this->panelProduct->Controls->Add(this->txtNamaProduk);
      this->panelProduct->Controls->Add(this->lblHarga);
      this->panelProduct->Controls->Add(this->txtHarga);
      this->panelProduct->Controls->Add(this->lblKomisi);
      this->panelProduct->Controls->Add(this->txtKomisi);
      this->panelProduct->Controls->Add(this->lblStok);
      this->panelProduct->Controls->Add(this->txtStok);
      this->panelProduct->Controls->Add(this->btnSaveProduct);
      this->panelProduct->Controls->Add(this->btnCancelProduct);
      this->panelProduct->Location = System::Drawing::Point(565, 50);
      this->panelProduct->Name = L"panelProduct";
      this->panelProduct->Size = System::Drawing::Size(260, 320);
      this->panelProduct->TabIndex = 6;
      this->panelProduct->Visible = false;
      // 
      // lblNamaProduk
      // 
      this->lblNamaProduk->AutoSize = true;
      this->lblNamaProduk->Location = System::Drawing::Point(24, 25);
      this->lblNamaProduk->Name = L"lblNamaProduk";
      this->lblNamaProduk->Size = System::Drawing::Size(75, 13);
      this->lblNamaProduk->TabIndex = 0;
      this->lblNamaProduk->Text = L"Nama Produk:";
      // 
      // txtNamaProduk
      // 
      this->txtNamaProduk->Location = System::Drawing::Point(24, 45);
      this->txtNamaProduk->Name = L"txtNamaProduk";
      this->txtNamaProduk->Size = System::Drawing::Size(210, 20);
      this->txtNamaProduk->TabIndex = 1;
      // 
      // lblHarga
      // 
      this->lblHarga->AutoSize = true;
      this->lblHarga->Location = System::Drawing::Point(24, 85);
      this->lblHarga->Name = L"lblHarga";
      this->lblHarga->Size = System::Drawing::Size(62, 13);
      this->lblHarga->TabIndex = 2;
      this->lblHarga->Text = L"Harga (Rp):";
      // 
      // txtHarga
      // 
      this->txtHarga->Location = System::Drawing::Point(24, 105);
      this->txtHarga->Name = L"txtHarga";
      this->txtHarga->Size = System::Drawing::Size(210, 20);
      this->txtHarga->TabIndex = 3;
      // 
      // lblKomisi
      // 
      this->lblKomisi->AutoSize = true;
      this->lblKomisi->Location = System::Drawing::Point(24, 199);
      this->lblKomisi->Name = L"lblKomisi";
      this->lblKomisi->Size = System::Drawing::Size(144, 13);
      this->lblKomisi->TabIndex = 4;
      this->lblKomisi->Text = L"Komisi Aplikasi: 5% (otomatis)";
      // 
      // txtKomisi
      // 
      this->txtKomisi->BackColor = System::Drawing::Color::LightGray;
      this->txtKomisi->Location = System::Drawing::Point(24, 219);
      this->txtKomisi->Name = L"txtKomisi";
      this->txtKomisi->ReadOnly = true;
      this->txtKomisi->Size = System::Drawing::Size(210, 20);
      this->txtKomisi->TabIndex = 5;
      this->txtKomisi->Text = L"5";
      this->txtKomisi->Visible = false;
      // 
      // lblStok
      // 
      this->lblStok->AutoSize = true;
      this->lblStok->Location = System::Drawing::Point(24, 142);
      this->lblStok->Name = L"lblStok";
      this->lblStok->Size = System::Drawing::Size(32, 13);
      this->lblStok->TabIndex = 6;
      this->lblStok->Text = L"Stok:";
      // 
      // txtStok
      // 
      this->txtStok->Location = System::Drawing::Point(24, 162);
      this->txtStok->Name = L"txtStok";
      this->txtStok->Size = System::Drawing::Size(210, 20);
      this->txtStok->TabIndex = 6;
      this->txtStok->Text = L"0";
      // 
      // btnSaveProduct
      // 
      this->btnSaveProduct->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
          static_cast<System::Int32>(static_cast<System::Byte>(69)));
      this->btnSaveProduct->ForeColor = System::Drawing::Color::White;
      this->btnSaveProduct->Location = System::Drawing::Point(24, 267);
      this->btnSaveProduct->Name = L"btnSaveProduct";
      this->btnSaveProduct->Size = System::Drawing::Size(100, 30);
      this->btnSaveProduct->TabIndex = 7;
      this->btnSaveProduct->Text = L"Simpan";
      this->btnSaveProduct->UseVisualStyleBackColor = false;
      this->btnSaveProduct->Click += gcnew System::EventHandler(this, &merchantForm::btnSaveProduct_Click);
      // 
      // btnCancelProduct
      // 
      this->btnCancelProduct->Location = System::Drawing::Point(134, 267);
      this->btnCancelProduct->Name = L"btnCancelProduct";
      this->btnCancelProduct->Size = System::Drawing::Size(100, 30);
      this->btnCancelProduct->TabIndex = 8;
      this->btnCancelProduct->Text = L"Batal";
      this->btnCancelProduct->UseVisualStyleBackColor = true;
      this->btnCancelProduct->Click += gcnew System::EventHandler(this, &merchantForm::btnCancelProduct_Click);
      // 
      // tabSales
      // 
      this->tabSales->Controls->Add(this->lblSalesTitle);
      this->tabSales->Controls->Add(this->dgvSales);
      this->tabSales->Controls->Add(this->btnRefreshSales);
      this->tabSales->Location = System::Drawing::Point(4, 22);
      this->tabSales->Name = L"tabSales";
      this->tabSales->Size = System::Drawing::Size(852, 454);
      this->tabSales->TabIndex = 2;
      this->tabSales->Text = L"Penjualan";
      this->tabSales->UseVisualStyleBackColor = true;
      // 
      // lblSalesTitle
      // 
      this->lblSalesTitle->AutoSize = true;
      this->lblSalesTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblSalesTitle->Location = System::Drawing::Point(15, 15);
      this->lblSalesTitle->Name = L"lblSalesTitle";
      this->lblSalesTitle->Size = System::Drawing::Size(173, 25);
      this->lblSalesTitle->TabIndex = 0;
      this->lblSalesTitle->Text = L"Riwayat Penjualan";
      // 
      // dgvSales
      // 
      this->dgvSales->AllowUserToAddRows = false;
      this->dgvSales->AllowUserToDeleteRows = false;
      this->dgvSales->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvSales->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvSales->Location = System::Drawing::Point(15, 50);
      this->dgvSales->MultiSelect = false;
      this->dgvSales->Name = L"dgvSales";
      this->dgvSales->ReadOnly = true;
      this->dgvSales->Size = System::Drawing::Size(820, 340);
      this->dgvSales->TabIndex = 1;
      // 
      // btnRefreshSales
      // 
      this->btnRefreshSales->Location = System::Drawing::Point(15, 406);
      this->btnRefreshSales->Name = L"btnRefreshSales";
      this->btnRefreshSales->Size = System::Drawing::Size(100, 30);
      this->btnRefreshSales->TabIndex = 2;
      this->btnRefreshSales->Text = L"Refresh";
      this->btnRefreshSales->UseVisualStyleBackColor = true;
      this->btnRefreshSales->Click += gcnew System::EventHandler(this, &merchantForm::btnRefreshSales_Click);
      // 
      // tabProfile
      // 
      this->tabProfile->Controls->Add(this->lblProfileTitle);
      this->tabProfile->Controls->Add(this->lblAlamatToko);
      this->tabProfile->Controls->Add(this->txtAlamatToko);
      this->tabProfile->Controls->Add(this->btnSaveAlamat);
      this->tabProfile->Controls->Add(this->lblAlamatInfo);
      this->tabProfile->Location = System::Drawing::Point(4, 22);
      this->tabProfile->Name = L"tabProfile";
      this->tabProfile->Size = System::Drawing::Size(852, 454);
      this->tabProfile->TabIndex = 3;
      this->tabProfile->Text = L"Profil Toko";
      this->tabProfile->UseVisualStyleBackColor = true;
      // 
      // lblProfileTitle
      // 
      this->lblProfileTitle->AutoSize = true;
      this->lblProfileTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblProfileTitle->Location = System::Drawing::Point(15, 15);
      this->lblProfileTitle->Name = L"lblProfileTitle";
      this->lblProfileTitle->Size = System::Drawing::Size(110, 25);
      this->lblProfileTitle->TabIndex = 0;
      this->lblProfileTitle->Text = L"Profil Toko";
      // 
      // lblAlamatToko
      // 
      this->lblAlamatToko->AutoSize = true;
      this->lblAlamatToko->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->lblAlamatToko->Location = System::Drawing::Point(15, 60);
      this->lblAlamatToko->Name = L"lblAlamatToko";
      this->lblAlamatToko->Size = System::Drawing::Size(89, 20);
      this->lblAlamatToko->TabIndex = 1;
      this->lblAlamatToko->Text = L"Lokasi Toko:";
      // 
      // txtAlamatToko
      // 
      this->txtAlamatToko->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->txtAlamatToko->Location = System::Drawing::Point(15, 85);
      this->txtAlamatToko->Multiline = true;
      this->txtAlamatToko->Name = L"txtAlamatToko";
      this->txtAlamatToko->Size = System::Drawing::Size(369, 80);
      this->txtAlamatToko->TabIndex = 2;
      // 
      // btnSaveAlamat
      // 
      this->btnSaveAlamat->BackColor = System::Drawing::Color::MediumSeaGreen;
      this->btnSaveAlamat->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
      this->btnSaveAlamat->ForeColor = System::Drawing::Color::White;
      this->btnSaveAlamat->Location = System::Drawing::Point(15, 198);
      this->btnSaveAlamat->Name = L"btnSaveAlamat";
      this->btnSaveAlamat->Size = System::Drawing::Size(150, 35);
      this->btnSaveAlamat->TabIndex = 3;
      this->btnSaveAlamat->Text = L"Simpan Lokasi";
      this->btnSaveAlamat->UseVisualStyleBackColor = false;
      this->btnSaveAlamat->Click += gcnew System::EventHandler(this, &merchantForm::btnSaveAlamat_Click);
      // 
      // lblAlamatInfo
      // 
      this->lblAlamatInfo->AutoSize = true;
      this->lblAlamatInfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
      this->lblAlamatInfo->ForeColor = System::Drawing::Color::Gray;
      this->lblAlamatInfo->Location = System::Drawing::Point(15, 180);
      this->lblAlamatInfo->Name = L"lblAlamatInfo";
      this->lblAlamatInfo->Size = System::Drawing::Size(369, 15);
      this->lblAlamatInfo->TabIndex = 4;
      this->lblAlamatInfo->Text = L"Lokasi toko akan ditampilkan kepada kurir saat pengambilan barang.";
      // 
      // btnLogout
      // 
      this->btnLogout->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(53)),
          static_cast<System::Int32>(static_cast<System::Byte>(69)));
      this->btnLogout->ForeColor = System::Drawing::Color::White;
      this->btnLogout->Location = System::Drawing::Point(778, 499);
      this->btnLogout->Name = L"btnLogout";
      this->btnLogout->Size = System::Drawing::Size(90, 30);
      this->btnLogout->TabIndex = 1;
      this->btnLogout->Text = L"Logout";
      this->btnLogout->UseVisualStyleBackColor = false;
      this->btnLogout->Click += gcnew System::EventHandler(this, &merchantForm::btnLogout_Click);
      // 
      // merchantForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::FloralWhite;
      this->ClientSize = System::Drawing::Size(884, 541);
      this->Controls->Add(this->tabControl);
      this->Controls->Add(this->btnLogout);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->MaximizeBox = false;
      this->Name = L"merchantForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Merchant Dashboard - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &merchantForm::merchantForm_Load);
      this->tabControl->ResumeLayout(false);
      this->tabDashboard->ResumeLayout(false);
      this->tabDashboard->PerformLayout();
      this->tabProducts->ResumeLayout(false);
      this->tabProducts->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvProducts))->EndInit();
      this->panelProduct->ResumeLayout(false);
      this->panelProduct->PerformLayout();
      this->tabSales->ResumeLayout(false);
      this->tabSales->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSales))->EndInit();
      this->tabProfile->ResumeLayout(false);
      this->tabProfile->PerformLayout();
      this->ResumeLayout(false);

  }
#pragma endregion

  // ========== Event Handlers (implementations in merchantForm.cpp) ==========
private:
  System::Void merchantForm_Load(System::Object ^ sender,
                                 System::EventArgs ^ e);
  void LoadDashboard();
  void LoadProducts();
  void LoadSales();
  void ClearProductForm();
  System::Void btnRefreshDashboard_Click(System::Object ^ sender,
                                         System::EventArgs ^ e);
  System::Void btnRefreshProducts_Click(System::Object ^ sender,
                                        System::EventArgs ^ e);
  System::Void btnAddProduct_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void btnEditProduct_Click(System::Object ^ sender,
                                    System::EventArgs ^ e);
  System::Void btnDeleteProduct_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  System::Void btnSaveProduct_Click(System::Object ^ sender,
                                    System::EventArgs ^ e);
  System::Void btnCancelProduct_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  System::Void btnRefreshSales_Click(System::Object ^ sender,
                                     System::EventArgs ^ e);
  void LoadProfile();
  System::Void btnSaveAlamat_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void btnAddStock_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  System::Void btnWithdraw_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
};
} // namespace ECommerce
