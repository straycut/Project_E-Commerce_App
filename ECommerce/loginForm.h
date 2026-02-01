#pragma once
#include "DatabaseManager.h"
#include "adminForm.h"
#include "courierForm.h"
#include "customerForm.h"
#include "merchantForm.h"
#include "registrationForm.h"

namespace ECommerce {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for loginF
/// </summary>
public
ref class loginF : public System::Windows::Forms::Form {
public:
  loginF(void) {
    InitializeComponent();
    // Initialize database on application start
    DatabaseManager::InitializeDatabase();
  }

protected:
  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  ~loginF() {
    if (components) {
      delete components;
    }
  }

private:
  System::Windows::Forms::Label ^ label1;

protected:
private:
  System::Windows::Forms::Label ^ labelNama;

private:
  System::Windows::Forms::Label ^ labelSandi;

private:
  System::Windows::Forms::TextBox ^ textBoxNama;

private:
  System::Windows::Forms::TextBox ^ textBoxSandi;

private:
  System::Windows::Forms::Button ^ btnDaftar;

private:
  System::Windows::Forms::Button ^ btnMasuk;

private:
  System::Windows::Forms::Label ^ label2;

private:
  System::Windows::Forms::PictureBox ^ pictureBox1;

private:
  /// <summary>
  /// Required designer variable.
  /// </summary>
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  /// <summary>
  /// Required method for Designer support - do not modify
  /// the contents of this method with the code editor.
  /// </summary>
  void InitializeComponent(void) {
      System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(loginF::typeid));
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->labelNama = (gcnew System::Windows::Forms::Label());
      this->labelSandi = (gcnew System::Windows::Forms::Label());
      this->textBoxNama = (gcnew System::Windows::Forms::TextBox());
      this->textBoxSandi = (gcnew System::Windows::Forms::TextBox());
      this->btnDaftar = (gcnew System::Windows::Forms::Button());
      this->btnMasuk = (gcnew System::Windows::Forms::Button());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
      this->SuspendLayout();
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->BackColor = System::Drawing::Color::Transparent;
      this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
      this->label1->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->label1->Location = System::Drawing::Point(102, 252);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(171, 37);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Welcome to";
      // 
      // labelNama
      // 
      this->labelNama->AutoSize = true;
      this->labelNama->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
      this->labelNama->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(37)),
          static_cast<System::Int32>(static_cast<System::Byte>(41)));
      this->labelNama->Location = System::Drawing::Point(436, 108);
      this->labelNama->Name = L"labelNama";
      this->labelNama->Size = System::Drawing::Size(71, 19);
      this->labelNama->TabIndex = 6;
      this->labelNama->Text = L"Username";
      // 
      // labelSandi
      // 
      this->labelSandi->AutoSize = true;
      this->labelSandi->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
      this->labelSandi->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(37)),
          static_cast<System::Int32>(static_cast<System::Byte>(41)));
      this->labelSandi->Location = System::Drawing::Point(436, 178);
      this->labelSandi->Name = L"labelSandi";
      this->labelSandi->Size = System::Drawing::Size(67, 19);
      this->labelSandi->TabIndex = 5;
      this->labelSandi->Text = L"Password";
      // 
      // textBoxNama
      // 
      this->textBoxNama->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->textBoxNama->Location = System::Drawing::Point(440, 133);
      this->textBoxNama->Name = L"textBoxNama";
      this->textBoxNama->Size = System::Drawing::Size(240, 27);
      this->textBoxNama->TabIndex = 1;
      // 
      // textBoxSandi
      // 
      this->textBoxSandi->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->textBoxSandi->Location = System::Drawing::Point(440, 203);
      this->textBoxSandi->Name = L"textBoxSandi";
      this->textBoxSandi->PasswordChar = '*';
      this->textBoxSandi->Size = System::Drawing::Size(240, 27);
      this->textBoxSandi->TabIndex = 2;
      // 
      // btnDaftar
      // 
      this->btnDaftar->BackColor = System::Drawing::Color::Transparent;
      this->btnDaftar->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
          static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
      this->btnDaftar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->btnDaftar->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->btnDaftar->Location = System::Drawing::Point(440, 299);
      this->btnDaftar->Name = L"btnDaftar";
      this->btnDaftar->Size = System::Drawing::Size(240, 35);
      this->btnDaftar->TabIndex = 4;
      this->btnDaftar->Text = L"Belum punya akun\? Daftar";
      this->btnDaftar->UseVisualStyleBackColor = false;
      this->btnDaftar->Click += gcnew System::EventHandler(this, &loginF::btnDaftar_Click);
      // 
      // btnMasuk
      // 
      this->btnMasuk->BackColor = System::Drawing::Color::MediumSeaGreen;
      this->btnMasuk->FlatAppearance->BorderSize = 0;
      this->btnMasuk->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
      this->btnMasuk->ForeColor = System::Drawing::Color::White;
      this->btnMasuk->Location = System::Drawing::Point(440, 253);
      this->btnMasuk->Name = L"btnMasuk";
      this->btnMasuk->Size = System::Drawing::Size(240, 40);
      this->btnMasuk->TabIndex = 3;
      this->btnMasuk->Text = L"Masuk";
      this->btnMasuk->UseVisualStyleBackColor = false;
      this->btnMasuk->Click += gcnew System::EventHandler(this, &loginF::btnMasuk_Click);
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->BackColor = System::Drawing::Color::Transparent;
      this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
      this->label2->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->label2->Location = System::Drawing::Point(96, 281);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(180, 37);
      this->label2->TabIndex = 7;
      this->label2->Text = L"E-Commerce";
      // 
      // pictureBox1
      // 
      this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
      this->pictureBox1->Location = System::Drawing::Point(110, 122);
      this->pictureBox1->Name = L"pictureBox1";
      this->pictureBox1->Size = System::Drawing::Size(150, 102);
      this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
      this->pictureBox1->TabIndex = 8;
      this->pictureBox1->TabStop = false;
      // 
      // loginF
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::FloralWhite;
      this->ClientSize = System::Drawing::Size(784, 441);
      this->Controls->Add(this->pictureBox1);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->btnMasuk);
      this->Controls->Add(this->btnDaftar);
      this->Controls->Add(this->textBoxSandi);
      this->Controls->Add(this->textBoxNama);
      this->Controls->Add(this->labelSandi);
      this->Controls->Add(this->labelNama);
      this->Controls->Add(this->label1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->MaximizeBox = false;
      this->Name = L"loginF";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Login - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &loginF::loginF_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

  }
#pragma endregion

  // ========== Event Handlers (implementations in loginForm.cpp) ==========
private:
  System::Void btnDaftar_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnMasuk_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void loginF_Load(System::Object ^ sender, System::EventArgs ^ e);
};
} // namespace ECommerce
