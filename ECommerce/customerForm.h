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
  int currentSaldo;

  customerForm(void) {
    InitializeComponent();
    currentUserID = 0;
    currentUsername = "";
    currentSaldo = 0;
  }

  customerForm(int userID, String ^ username) {
    InitializeComponent();
    currentUserID = userID;
    currentUsername = username;
    currentSaldo = 0;
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
  System::Windows::Forms::TabPage ^ tabSaldo;

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

  // History
private:
  System::Windows::Forms::Label ^ lblHistoryTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvHistory;

private:
  System::Windows::Forms::Button ^ btnRefreshHistory;

  // Saldo
private:
  System::Windows::Forms::Label ^ lblSaldoTitle;

private:
  System::Windows::Forms::Label ^ lblCurrentSaldo;

private:
  System::Windows::Forms::Label ^ lblTopUpAmount;

private:
  System::Windows::Forms::TextBox ^ txtTopUpAmount;

private:
  System::Windows::Forms::Button ^ btnTopUp;

private:
  System::Windows::Forms::Button ^ btnLogout;

private:
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
    this->tabControl = (gcnew System::Windows::Forms::TabControl());
    this->tabCatalog = (gcnew System::Windows::Forms::TabPage());
    this->tabHistory = (gcnew System::Windows::Forms::TabPage());
    this->tabSaldo = (gcnew System::Windows::Forms::TabPage());
    this->lblCatalogTitle = (gcnew System::Windows::Forms::Label());
    this->dgvProducts = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshCatalog = (gcnew System::Windows::Forms::Button());
    this->btnBuy = (gcnew System::Windows::Forms::Button());
    this->lblSaldoInfo = (gcnew System::Windows::Forms::Label());
    this->lblHistoryTitle = (gcnew System::Windows::Forms::Label());
    this->dgvHistory = (gcnew System::Windows::Forms::DataGridView());
    this->btnRefreshHistory = (gcnew System::Windows::Forms::Button());
    this->lblSaldoTitle = (gcnew System::Windows::Forms::Label());
    this->lblCurrentSaldo = (gcnew System::Windows::Forms::Label());
    this->lblTopUpAmount = (gcnew System::Windows::Forms::Label());
    this->txtTopUpAmount = (gcnew System::Windows::Forms::TextBox());
    this->btnTopUp = (gcnew System::Windows::Forms::Button());
    this->btnLogout = (gcnew System::Windows::Forms::Button());
    this->tabControl->SuspendLayout();
    this->tabCatalog->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvProducts))
        ->BeginInit();
    this->tabHistory->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvHistory))
        ->BeginInit();
    this->tabSaldo->SuspendLayout();
    this->SuspendLayout();
    //
    // tabControl
    //
    this->tabControl->Controls->Add(this->tabCatalog);
    this->tabControl->Controls->Add(this->tabHistory);
    this->tabControl->Controls->Add(this->tabSaldo);
    this->tabControl->Location = System::Drawing::Point(12, 12);
    this->tabControl->Name = L"tabControl";
    this->tabControl->SelectedIndex = 0;
    this->tabControl->Size = System::Drawing::Size(760, 480);
    this->tabControl->TabIndex = 0;
    //
    // tabCatalog
    //
    this->tabCatalog->Controls->Add(this->lblCatalogTitle);
    this->tabCatalog->Controls->Add(this->dgvProducts);
    this->tabCatalog->Controls->Add(this->btnRefreshCatalog);
    this->tabCatalog->Controls->Add(this->btnBuy);
    this->tabCatalog->Controls->Add(this->lblSaldoInfo);
    this->tabCatalog->Location = System::Drawing::Point(4, 22);
    this->tabCatalog->Name = L"tabCatalog";
    this->tabCatalog->Padding = System::Windows::Forms::Padding(3);
    this->tabCatalog->Size = System::Drawing::Size(752, 454);
    this->tabCatalog->TabIndex = 0;
    this->tabCatalog->Text = L"Katalog Produk";
    this->tabCatalog->UseVisualStyleBackColor = true;
    //
    // lblCatalogTitle
    //
    this->lblCatalogTitle->AutoSize = true;
    this->lblCatalogTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblCatalogTitle->Location = System::Drawing::Point(15, 15);
    this->lblCatalogTitle->Name = L"lblCatalogTitle";
    this->lblCatalogTitle->Size = System::Drawing::Size(150, 25);
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
    this->dgvProducts->Size = System::Drawing::Size(720, 320);
    this->dgvProducts->TabIndex = 1;
    //
    // btnRefreshCatalog
    //
    this->btnRefreshCatalog->Location = System::Drawing::Point(15, 380);
    this->btnRefreshCatalog->Name = L"btnRefreshCatalog";
    this->btnRefreshCatalog->Size = System::Drawing::Size(100, 30);
    this->btnRefreshCatalog->TabIndex = 2;
    this->btnRefreshCatalog->Text = L"Refresh";
    this->btnRefreshCatalog->UseVisualStyleBackColor = true;
    this->btnRefreshCatalog->Click += gcnew System::EventHandler(
        this, &customerForm::btnRefreshCatalog_Click);
    //
    // btnBuy
    //
    this->btnBuy->BackColor = System::Drawing::Color::LightGreen;
    this->btnBuy->Font = (gcnew System::Drawing::Font(
        L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
    this->btnBuy->Location = System::Drawing::Point(125, 380);
    this->btnBuy->Name = L"btnBuy";
    this->btnBuy->Size = System::Drawing::Size(150, 30);
    this->btnBuy->TabIndex = 3;
    this->btnBuy->Text = L"Beli Produk";
    this->btnBuy->UseVisualStyleBackColor = false;
    this->btnBuy->Click +=
        gcnew System::EventHandler(this, &customerForm::btnBuy_Click);
    //
    // lblSaldoInfo
    //
    this->lblSaldoInfo->AutoSize = true;
    this->lblSaldoInfo->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
    this->lblSaldoInfo->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblSaldoInfo->Location = System::Drawing::Point(550, 15);
    this->lblSaldoInfo->Name = L"lblSaldoInfo";
    this->lblSaldoInfo->Size = System::Drawing::Size(100, 21);
    this->lblSaldoInfo->TabIndex = 4;
    this->lblSaldoInfo->Text = L"Saldo: Rp 0";
    //
    // tabHistory
    //
    this->tabHistory->Controls->Add(this->lblHistoryTitle);
    this->tabHistory->Controls->Add(this->dgvHistory);
    this->tabHistory->Controls->Add(this->btnRefreshHistory);
    this->tabHistory->Location = System::Drawing::Point(4, 22);
    this->tabHistory->Name = L"tabHistory";
    this->tabHistory->Size = System::Drawing::Size(752, 454);
    this->tabHistory->TabIndex = 1;
    this->tabHistory->Text = L"Riwayat Pembelian";
    this->tabHistory->UseVisualStyleBackColor = true;
    //
    // lblHistoryTitle
    //
    this->lblHistoryTitle->AutoSize = true;
    this->lblHistoryTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblHistoryTitle->Location = System::Drawing::Point(15, 15);
    this->lblHistoryTitle->Name = L"lblHistoryTitle";
    this->lblHistoryTitle->Size = System::Drawing::Size(200, 25);
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
    this->dgvHistory->Size = System::Drawing::Size(720, 340);
    this->dgvHistory->TabIndex = 1;
    //
    // btnRefreshHistory
    //
    this->btnRefreshHistory->Location = System::Drawing::Point(15, 400);
    this->btnRefreshHistory->Name = L"btnRefreshHistory";
    this->btnRefreshHistory->Size = System::Drawing::Size(100, 30);
    this->btnRefreshHistory->TabIndex = 2;
    this->btnRefreshHistory->Text = L"Refresh";
    this->btnRefreshHistory->UseVisualStyleBackColor = true;
    this->btnRefreshHistory->Click += gcnew System::EventHandler(
        this, &customerForm::btnRefreshHistory_Click);
    //
    // tabSaldo
    //
    this->tabSaldo->Controls->Add(this->lblSaldoTitle);
    this->tabSaldo->Controls->Add(this->lblCurrentSaldo);
    this->tabSaldo->Controls->Add(this->lblTopUpAmount);
    this->tabSaldo->Controls->Add(this->txtTopUpAmount);
    this->tabSaldo->Controls->Add(this->btnTopUp);
    this->tabSaldo->Location = System::Drawing::Point(4, 22);
    this->tabSaldo->Name = L"tabSaldo";
    this->tabSaldo->Size = System::Drawing::Size(752, 454);
    this->tabSaldo->TabIndex = 2;
    this->tabSaldo->Text = L"Saldo";
    this->tabSaldo->UseVisualStyleBackColor = true;
    //
    // lblSaldoTitle
    //
    this->lblSaldoTitle->AutoSize = true;
    this->lblSaldoTitle->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
    this->lblSaldoTitle->Location = System::Drawing::Point(15, 15);
    this->lblSaldoTitle->Name = L"lblSaldoTitle";
    this->lblSaldoTitle->Size = System::Drawing::Size(180, 25);
    this->lblSaldoTitle->TabIndex = 0;
    this->lblSaldoTitle->Text = L"Kelola Saldo Anda";
    //
    // lblCurrentSaldo
    //
    this->lblCurrentSaldo->AutoSize = true;
    this->lblCurrentSaldo->Font = (gcnew System::Drawing::Font(
        L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
    this->lblCurrentSaldo->ForeColor = System::Drawing::Color::DarkGreen;
    this->lblCurrentSaldo->Location = System::Drawing::Point(15, 60);
    this->lblCurrentSaldo->Name = L"lblCurrentSaldo";
    this->lblCurrentSaldo->Size = System::Drawing::Size(200, 32);
    this->lblCurrentSaldo->TabIndex = 1;
    this->lblCurrentSaldo->Text = L"Saldo: Rp 0";
    //
    // lblTopUpAmount
    //
    this->lblTopUpAmount->AutoSize = true;
    this->lblTopUpAmount->Location = System::Drawing::Point(15, 120);
    this->lblTopUpAmount->Name = L"lblTopUpAmount";
    this->lblTopUpAmount->Size = System::Drawing::Size(90, 13);
    this->lblTopUpAmount->TabIndex = 2;
    this->lblTopUpAmount->Text = L"Jumlah Top Up (Rp):";
    //
    // txtTopUpAmount
    //
    this->txtTopUpAmount->Font =
        (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
    this->txtTopUpAmount->Location = System::Drawing::Point(15, 140);
    this->txtTopUpAmount->Name = L"txtTopUpAmount";
    this->txtTopUpAmount->Size = System::Drawing::Size(200, 26);
    this->txtTopUpAmount->TabIndex = 3;
    this->txtTopUpAmount->Text = L"100000";
    //
    // btnTopUp
    //
    this->btnTopUp->BackColor = System::Drawing::Color::LightBlue;
    this->btnTopUp->Font = (gcnew System::Drawing::Font(
        L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
    this->btnTopUp->Location = System::Drawing::Point(15, 180);
    this->btnTopUp->Name = L"btnTopUp";
    this->btnTopUp->Size = System::Drawing::Size(200, 35);
    this->btnTopUp->TabIndex = 4;
    this->btnTopUp->Text = L"Top Up Saldo";
    this->btnTopUp->UseVisualStyleBackColor = false;
    this->btnTopUp->Click +=
        gcnew System::EventHandler(this, &customerForm::btnTopUp_Click);
    //
    // btnLogout
    //
    this->btnLogout->BackColor = System::Drawing::Color::LightGray;
    this->btnLogout->Location = System::Drawing::Point(680, 500);
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
    this->ClientSize = System::Drawing::Size(784, 541);
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
    this->tabHistory->ResumeLayout(false);
    this->tabHistory->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->dgvHistory))
        ->EndInit();
    this->tabSaldo->ResumeLayout(false);
    this->tabSaldo->PerformLayout();
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
  System::Void btnRefreshCatalog_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnBuy_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnRefreshHistory_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnTopUp_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
};
} // namespace ECommerce
