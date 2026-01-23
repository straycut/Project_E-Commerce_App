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
/// Courier Dashboard - Manage deliveries
/// </summary>
public
ref class courierForm : public System::Windows::Forms::Form {
public:
  int currentUserID;

public:
    String^ currentUsername;

  courierForm(void) {
    InitializeComponent();
    currentUserID = 0;
    currentUsername = "";
  }

  courierForm(int userID, String ^ username) {
    InitializeComponent();
    currentUserID = userID;
    currentUsername = username;
  }

protected:
  ~courierForm() {
    if (components) {
      delete components;
    }
  }

private:
  System::Windows::Forms::TabControl ^ tabControl;

private:
  System::Windows::Forms::TabPage ^ tabDashboard;

private:
  System::Windows::Forms::TabPage ^ tabPending;

private:
  System::Windows::Forms::TabPage ^ tabActive;

private:
  System::Windows::Forms::TabPage ^ tabHistory;

  // Dashboard
private:
  System::Windows::Forms::Label ^ lblTitle;

private:
  System::Windows::Forms::Label ^ lblTodayDeliveries;

private:
  System::Windows::Forms::Label ^ lblTotalDeliveries;

private:
  System::Windows::Forms::Label ^ lblTotalIncome;

private:
  System::Windows::Forms::Button ^ btnRefreshDashboard;

  // Pending
private:
  System::Windows::Forms::Label ^ lblPendingTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvPending;

private:
  System::Windows::Forms::Button ^ btnRefreshPending;

private:
  System::Windows::Forms::Button ^ btnClaim;

  // Active
private:
  System::Windows::Forms::Label ^ lblActiveTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvActive;

private:
  System::Windows::Forms::Button ^ btnRefreshActive;

private:
  System::Windows::Forms::Button ^ btnComplete;

  // History
private:
  System::Windows::Forms::Label ^ lblHistoryTitle;

private:
  System::Windows::Forms::DataGridView ^ dgvHistory;

private:
  System::Windows::Forms::Button ^ btnRefreshHistory;

private:
  System::Windows::Forms::Button ^ btnLogout;

private:
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
      this->tabControl = (gcnew System::Windows::Forms::TabControl());
      this->tabDashboard = (gcnew System::Windows::Forms::TabPage());
      this->lblTitle = (gcnew System::Windows::Forms::Label());
      this->lblTodayDeliveries = (gcnew System::Windows::Forms::Label());
      this->lblTotalDeliveries = (gcnew System::Windows::Forms::Label());
      this->lblTotalIncome = (gcnew System::Windows::Forms::Label());
      this->btnRefreshDashboard = (gcnew System::Windows::Forms::Button());
      this->tabPending = (gcnew System::Windows::Forms::TabPage());
      this->lblPendingTitle = (gcnew System::Windows::Forms::Label());
      this->dgvPending = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshPending = (gcnew System::Windows::Forms::Button());
      this->btnClaim = (gcnew System::Windows::Forms::Button());
      this->tabActive = (gcnew System::Windows::Forms::TabPage());
      this->lblActiveTitle = (gcnew System::Windows::Forms::Label());
      this->dgvActive = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshActive = (gcnew System::Windows::Forms::Button());
      this->btnComplete = (gcnew System::Windows::Forms::Button());
      this->tabHistory = (gcnew System::Windows::Forms::TabPage());
      this->lblHistoryTitle = (gcnew System::Windows::Forms::Label());
      this->dgvHistory = (gcnew System::Windows::Forms::DataGridView());
      this->btnRefreshHistory = (gcnew System::Windows::Forms::Button());
      this->btnLogout = (gcnew System::Windows::Forms::Button());
      this->tabControl->SuspendLayout();
      this->tabDashboard->SuspendLayout();
      this->tabPending->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPending))->BeginInit();
      this->tabActive->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvActive))->BeginInit();
      this->tabHistory->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistory))->BeginInit();
      this->SuspendLayout();
      // 
      // tabControl
      // 
      this->tabControl->Controls->Add(this->tabDashboard);
      this->tabControl->Controls->Add(this->tabPending);
      this->tabControl->Controls->Add(this->tabActive);
      this->tabControl->Controls->Add(this->tabHistory);
      this->tabControl->Location = System::Drawing::Point(12, 12);
      this->tabControl->Name = L"tabControl";
      this->tabControl->SelectedIndex = 0;
      this->tabControl->Size = System::Drawing::Size(860, 480);
      this->tabControl->TabIndex = 0;
      // 
      // tabDashboard
      // 
      this->tabDashboard->Controls->Add(this->lblTitle);
      this->tabDashboard->Controls->Add(this->lblTodayDeliveries);
      this->tabDashboard->Controls->Add(this->lblTotalDeliveries);
      this->tabDashboard->Controls->Add(this->lblTotalIncome);
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
      this->lblTitle->Location = System::Drawing::Point(20, 21);
      this->lblTitle->Name = L"lblTitle";
      this->lblTitle->Size = System::Drawing::Size(230, 32);
      this->lblTitle->TabIndex = 0;
      this->lblTitle->Text = L"Courier Dashboard";
      // 
      // lblTodayDeliveries
      // 
      this->lblTodayDeliveries->AutoSize = true;
      this->lblTodayDeliveries->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
      this->lblTodayDeliveries->Location = System::Drawing::Point(21, 99);
      this->lblTodayDeliveries->Name = L"lblTodayDeliveries";
      this->lblTodayDeliveries->Size = System::Drawing::Size(193, 25);
      this->lblTodayDeliveries->TabIndex = 1;
      this->lblTodayDeliveries->Text = L"Pengiriman Hari Ini: 0";
      // 
      // lblTotalDeliveries
      // 
      this->lblTotalDeliveries->AutoSize = true;
      this->lblTotalDeliveries->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
      this->lblTotalDeliveries->Location = System::Drawing::Point(21, 124);
      this->lblTotalDeliveries->Name = L"lblTotalDeliveries";
      this->lblTotalDeliveries->Size = System::Drawing::Size(172, 25);
      this->lblTotalDeliveries->TabIndex = 2;
      this->lblTotalDeliveries->Text = L"Total Pengiriman: 0";
      // 
      // lblTotalIncome
      // 
      this->lblTotalIncome->AutoSize = true;
      this->lblTotalIncome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblTotalIncome->ForeColor = System::Drawing::Color::DarkGreen;
      this->lblTotalIncome->Location = System::Drawing::Point(21, 149);
      this->lblTotalIncome->Name = L"lblTotalIncome";
      this->lblTotalIncome->Size = System::Drawing::Size(168, 25);
      this->lblTotalIncome->TabIndex = 3;
      this->lblTotalIncome->Text = L"Pendapatan: Rp 0";
      // 
      // btnRefreshDashboard
      // 
      this->btnRefreshDashboard->Location = System::Drawing::Point(26, 398);
      this->btnRefreshDashboard->Name = L"btnRefreshDashboard";
      this->btnRefreshDashboard->Size = System::Drawing::Size(93, 30);
      this->btnRefreshDashboard->TabIndex = 4;
      this->btnRefreshDashboard->Text = L"Refresh";
      this->btnRefreshDashboard->UseVisualStyleBackColor = true;
      this->btnRefreshDashboard->Click += gcnew System::EventHandler(this, &courierForm::btnRefreshDashboard_Click);
      // 
      // tabPending
      // 
      this->tabPending->Controls->Add(this->lblPendingTitle);
      this->tabPending->Controls->Add(this->dgvPending);
      this->tabPending->Controls->Add(this->btnRefreshPending);
      this->tabPending->Controls->Add(this->btnClaim);
      this->tabPending->Location = System::Drawing::Point(4, 22);
      this->tabPending->Name = L"tabPending";
      this->tabPending->Size = System::Drawing::Size(852, 454);
      this->tabPending->TabIndex = 1;
      this->tabPending->Text = L"Pesanan Baru";
      this->tabPending->UseVisualStyleBackColor = true;
      // 
      // lblPendingTitle
      // 
      this->lblPendingTitle->AutoSize = true;
      this->lblPendingTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblPendingTitle->Location = System::Drawing::Point(10, 22);
      this->lblPendingTitle->Name = L"lblPendingTitle";
      this->lblPendingTitle->Size = System::Drawing::Size(240, 25);
      this->lblPendingTitle->TabIndex = 0;
      this->lblPendingTitle->Text = L"Pesanan Menunggu Kurir";
      // 
      // dgvPending
      // 
      this->dgvPending->AllowUserToAddRows = false;
      this->dgvPending->AllowUserToDeleteRows = false;
      this->dgvPending->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvPending->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvPending->Location = System::Drawing::Point(15, 50);
      this->dgvPending->MultiSelect = false;
      this->dgvPending->Name = L"dgvPending";
      this->dgvPending->ReadOnly = true;
      this->dgvPending->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
      this->dgvPending->Size = System::Drawing::Size(825, 350);
      this->dgvPending->TabIndex = 1;
      // 
      // btnRefreshPending
      // 
      this->btnRefreshPending->Location = System::Drawing::Point(15, 406);
      this->btnRefreshPending->Name = L"btnRefreshPending";
      this->btnRefreshPending->Size = System::Drawing::Size(100, 30);
      this->btnRefreshPending->TabIndex = 2;
      this->btnRefreshPending->Text = L"Refresh";
      this->btnRefreshPending->UseVisualStyleBackColor = true;
      this->btnRefreshPending->Click += gcnew System::EventHandler(this, &courierForm::btnRefreshPending_Click);
      // 
      // btnClaim
      // 
      this->btnClaim->BackColor = System::Drawing::Color::White;
      this->btnClaim->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
      this->btnClaim->Location = System::Drawing::Point(125, 406);
      this->btnClaim->Name = L"btnClaim";
      this->btnClaim->Size = System::Drawing::Size(150, 30);
      this->btnClaim->TabIndex = 3;
      this->btnClaim->Text = L"Ambil Pesanan";
      this->btnClaim->UseVisualStyleBackColor = false;
      this->btnClaim->Click += gcnew System::EventHandler(this, &courierForm::btnClaim_Click);
      // 
      // tabActive
      // 
      this->tabActive->Controls->Add(this->lblActiveTitle);
      this->tabActive->Controls->Add(this->dgvActive);
      this->tabActive->Controls->Add(this->btnRefreshActive);
      this->tabActive->Controls->Add(this->btnComplete);
      this->tabActive->Location = System::Drawing::Point(4, 22);
      this->tabActive->Name = L"tabActive";
      this->tabActive->Size = System::Drawing::Size(852, 454);
      this->tabActive->TabIndex = 2;
      this->tabActive->Text = L"Sedang Kirim";
      this->tabActive->UseVisualStyleBackColor = true;
      // 
      // lblActiveTitle
      // 
      this->lblActiveTitle->AutoSize = true;
      this->lblActiveTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblActiveTitle->Location = System::Drawing::Point(10, 22);
      this->lblActiveTitle->Name = L"lblActiveTitle";
      this->lblActiveTitle->Size = System::Drawing::Size(162, 25);
      this->lblActiveTitle->TabIndex = 0;
      this->lblActiveTitle->Text = L"Pengiriman Aktif";
      // 
      // dgvActive
      // 
      this->dgvActive->AllowUserToAddRows = false;
      this->dgvActive->AllowUserToDeleteRows = false;
      this->dgvActive->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvActive->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvActive->Location = System::Drawing::Point(15, 50);
      this->dgvActive->MultiSelect = false;
      this->dgvActive->Name = L"dgvActive";
      this->dgvActive->ReadOnly = true;
      this->dgvActive->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
      this->dgvActive->Size = System::Drawing::Size(823, 350);
      this->dgvActive->TabIndex = 1;
      // 
      // btnRefreshActive
      // 
      this->btnRefreshActive->Location = System::Drawing::Point(15, 406);
      this->btnRefreshActive->Name = L"btnRefreshActive";
      this->btnRefreshActive->Size = System::Drawing::Size(100, 30);
      this->btnRefreshActive->TabIndex = 2;
      this->btnRefreshActive->Text = L"Refresh";
      this->btnRefreshActive->UseVisualStyleBackColor = true;
      this->btnRefreshActive->Click += gcnew System::EventHandler(this, &courierForm::btnRefreshActive_Click);
      // 
      // btnComplete
      // 
      this->btnComplete->BackColor = System::Drawing::Color::White;
      this->btnComplete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
      this->btnComplete->Location = System::Drawing::Point(125, 406);
      this->btnComplete->Name = L"btnComplete";
      this->btnComplete->Size = System::Drawing::Size(150, 30);
      this->btnComplete->TabIndex = 3;
      this->btnComplete->Text = L"Selesai Kirim";
      this->btnComplete->UseVisualStyleBackColor = false;
      this->btnComplete->Click += gcnew System::EventHandler(this, &courierForm::btnComplete_Click);
      // 
      // tabHistory
      // 
      this->tabHistory->Controls->Add(this->lblHistoryTitle);
      this->tabHistory->Controls->Add(this->dgvHistory);
      this->tabHistory->Controls->Add(this->btnRefreshHistory);
      this->tabHistory->Location = System::Drawing::Point(4, 22);
      this->tabHistory->Name = L"tabHistory";
      this->tabHistory->Size = System::Drawing::Size(852, 454);
      this->tabHistory->TabIndex = 3;
      this->tabHistory->Text = L"Riwayat";
      this->tabHistory->UseVisualStyleBackColor = true;
      // 
      // lblHistoryTitle
      // 
      this->lblHistoryTitle->AutoSize = true;
      this->lblHistoryTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
      this->lblHistoryTitle->Location = System::Drawing::Point(10, 22);
      this->lblHistoryTitle->Name = L"lblHistoryTitle";
      this->lblHistoryTitle->Size = System::Drawing::Size(188, 25);
      this->lblHistoryTitle->TabIndex = 0;
      this->lblHistoryTitle->Text = L"Riwayat Pengiriman";
      // 
      // dgvHistory
      // 
      this->dgvHistory->AllowUserToAddRows = false;
      this->dgvHistory->AllowUserToDeleteRows = false;
      this->dgvHistory->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvHistory->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvHistory->Location = System::Drawing::Point(15, 50);
      this->dgvHistory->Name = L"dgvHistory";
      this->dgvHistory->ReadOnly = true;
      this->dgvHistory->Size = System::Drawing::Size(824, 353);
      this->dgvHistory->TabIndex = 1;
      // 
      // btnRefreshHistory
      // 
      this->btnRefreshHistory->Location = System::Drawing::Point(15, 409);
      this->btnRefreshHistory->Name = L"btnRefreshHistory";
      this->btnRefreshHistory->Size = System::Drawing::Size(100, 30);
      this->btnRefreshHistory->TabIndex = 2;
      this->btnRefreshHistory->Text = L"Refresh";
      this->btnRefreshHistory->UseVisualStyleBackColor = true;
      this->btnRefreshHistory->Click += gcnew System::EventHandler(this, &courierForm::btnRefreshHistory_Click);
      // 
      // btnLogout
      // 
      this->btnLogout->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(53)),
          static_cast<System::Int32>(static_cast<System::Byte>(69)));
      this->btnLogout->FlatAppearance->BorderSize = 0;
      this->btnLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
      this->btnLogout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
      this->btnLogout->ForeColor = System::Drawing::Color::White;
      this->btnLogout->Location = System::Drawing::Point(782, 499);
      this->btnLogout->Name = L"btnLogout";
      this->btnLogout->Size = System::Drawing::Size(90, 30);
      this->btnLogout->TabIndex = 1;
      this->btnLogout->Text = L"Logout";
      this->btnLogout->UseVisualStyleBackColor = false;
      this->btnLogout->Click += gcnew System::EventHandler(this, &courierForm::btnLogout_Click);
      // 
      // courierForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::FloralWhite;
      this->ClientSize = System::Drawing::Size(884, 541);
      this->Controls->Add(this->tabControl);
      this->Controls->Add(this->btnLogout);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->MaximizeBox = false;
      this->Name = L"courierForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Courier Dashboard - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &courierForm::courierForm_Load);
      this->tabControl->ResumeLayout(false);
      this->tabDashboard->ResumeLayout(false);
      this->tabDashboard->PerformLayout();
      this->tabPending->ResumeLayout(false);
      this->tabPending->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPending))->EndInit();
      this->tabActive->ResumeLayout(false);
      this->tabActive->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvActive))->EndInit();
      this->tabHistory->ResumeLayout(false);
      this->tabHistory->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistory))->EndInit();
      this->ResumeLayout(false);

  }
#pragma endregion

  // ========== Event Handlers (implementations in courierForm.cpp) ==========
private:
  System::Void courierForm_Load(System::Object ^ sender, System::EventArgs ^ e);
  void LoadDashboard();
  void LoadPending();
  void LoadActive();
  void LoadHistory();
  System::Void btnRefreshDashboard_Click(System::Object ^ sender,
                                         System::EventArgs ^ e);
  System::Void btnRefreshPending_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnClaim_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnRefreshActive_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);
  System::Void btnComplete_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  System::Void btnRefreshHistory_Click(System::Object ^ sender,
                                       System::EventArgs ^ e);
  System::Void btnLogout_Click(System::Object ^ sender, System::EventArgs ^ e);
};
} // namespace ECommerce
