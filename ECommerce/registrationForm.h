#pragma once
#include "DatabaseManager.h"

namespace ECommerce {

/// <summary>
/// Summary for registerF
/// </summary>
public
ref class registerF : public System::Windows::Forms::Form {
public:
  registerF(void) { InitializeComponent(); }

protected:
  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  ~registerF() {
    if (components) {
      delete components;
    }
  }

private:
protected:
private:
private:
private:
private:
  System::Windows::Forms::Label ^ labelPassword;

private:
  System::Windows::Forms::Label ^ labelUsername;

private:
private:
  System::Windows::Forms::Label ^ labelRole;

private:
  System::Windows::Forms::ComboBox ^ comboBoxRole;

private:
  System::Windows::Forms::TextBox ^ textBoxPassword;

private:
  System::Windows::Forms::TextBox ^ textBoxUsername;

private:
  System::Windows::Forms::Label ^ label2;

private:
  System::Windows::Forms::Button ^ btnDaftar;

private:
  System::Windows::Forms::Label ^ label1;

private:
  System::Windows::Forms::Button ^ btnKembali;

private:
  System::Windows::Forms::Label ^ labelTitle;

private:
  /// <summary>
  /// Required designer variable.
  /// </summary>
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
      this->labelPassword = (gcnew System::Windows::Forms::Label());
      this->labelUsername = (gcnew System::Windows::Forms::Label());
      this->labelRole = (gcnew System::Windows::Forms::Label());
      this->comboBoxRole = (gcnew System::Windows::Forms::ComboBox());
      this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
      this->textBoxUsername = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->btnDaftar = (gcnew System::Windows::Forms::Button());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->btnKembali = (gcnew System::Windows::Forms::Button());
      this->labelTitle = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // labelPassword
      // 
      this->labelPassword->AutoSize = true;
      this->labelPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->labelPassword->Location = System::Drawing::Point(437, 157);
      this->labelPassword->Name = L"labelPassword";
      this->labelPassword->Size = System::Drawing::Size(64, 17);
      this->labelPassword->TabIndex = 9;
      this->labelPassword->Text = L"Password";
      // 
      // labelUsername
      // 
      this->labelUsername->AutoSize = true;
      this->labelUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->labelUsername->Location = System::Drawing::Point(437, 87);
      this->labelUsername->Name = L"labelUsername";
      this->labelUsername->Size = System::Drawing::Size(67, 17);
      this->labelUsername->TabIndex = 8;
      this->labelUsername->Text = L"Username";
      // 
      // labelRole
      // 
      this->labelRole->AutoSize = true;
      this->labelRole->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->labelRole->Location = System::Drawing::Point(437, 229);
      this->labelRole->Name = L"labelRole";
      this->labelRole->Size = System::Drawing::Size(64, 17);
      this->labelRole->TabIndex = 14;
      this->labelRole->Text = L"Pilih Role:";
      // 
      // comboBoxRole
      // 
      this->comboBoxRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->comboBoxRole->FormattingEnabled = true;
      this->comboBoxRole->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Merchant", L"Customer", L"Courier" });
      this->comboBoxRole->Location = System::Drawing::Point(440, 249);
      this->comboBoxRole->Name = L"comboBoxRole";
      this->comboBoxRole->Size = System::Drawing::Size(237, 21);
      this->comboBoxRole->TabIndex = 15;
      this->comboBoxRole->SelectedIndexChanged += gcnew System::EventHandler(this, &registerF::comboBoxRole_SelectedIndexChanged);
      // 
      // textBoxPassword
      // 
      this->textBoxPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->textBoxPassword->Location = System::Drawing::Point(440, 177);
      this->textBoxPassword->Name = L"textBoxPassword";
      this->textBoxPassword->PasswordChar = '*';
      this->textBoxPassword->Size = System::Drawing::Size(240, 27);
      this->textBoxPassword->TabIndex = 17;
      // 
      // textBoxUsername
      // 
      this->textBoxUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
      this->textBoxUsername->Location = System::Drawing::Point(440, 107);
      this->textBoxUsername->Name = L"textBoxUsername";
      this->textBoxUsername->Size = System::Drawing::Size(240, 27);
      this->textBoxUsername->TabIndex = 16;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->BackColor = System::Drawing::Color::Transparent;
      this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
      this->label2->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->label2->Location = System::Drawing::Point(122, 219);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(149, 37);
      this->label2->TabIndex = 25;
      this->label2->Text = L"Akun Baru";
      // 
      // btnDaftar
      // 
      this->btnDaftar->BackColor = System::Drawing::Color::MediumSeaGreen;
      this->btnDaftar->FlatAppearance->BorderSize = 0;
      this->btnDaftar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
      this->btnDaftar->ForeColor = System::Drawing::Color::White;
      this->btnDaftar->Location = System::Drawing::Point(440, 287);
      this->btnDaftar->Name = L"btnDaftar";
      this->btnDaftar->Size = System::Drawing::Size(240, 40);
      this->btnDaftar->TabIndex = 21;
      this->btnDaftar->Text = L"Daftar";
      this->btnDaftar->UseVisualStyleBackColor = false;
      this->btnDaftar->Click += gcnew System::EventHandler(this, &registerF::btnDaftar_Click);
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->BackColor = System::Drawing::Color::Transparent;
      this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
      this->label1->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->label1->Location = System::Drawing::Point(122, 182);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(143, 37);
      this->label1->TabIndex = 18;
      this->label1->Text = L"Registrasi";
      // 
      // btnKembali
      // 
      this->btnKembali->BackColor = System::Drawing::Color::Transparent;
      this->btnKembali->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
          static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
      this->btnKembali->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->btnKembali->ForeColor = System::Drawing::Color::MediumSeaGreen;
      this->btnKembali->Location = System::Drawing::Point(440, 333);
      this->btnKembali->Name = L"btnKembali";
      this->btnKembali->Size = System::Drawing::Size(240, 35);
      this->btnKembali->TabIndex = 26;
      this->btnKembali->Text = L"Kembali";
      this->btnKembali->UseVisualStyleBackColor = false;
      this->btnKembali->Click += gcnew System::EventHandler(this, &registerF::btnKembali_Click);
      // 
      // labelTitle
      // 
      this->labelTitle->AutoSize = true;
      this->labelTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
          static_cast<System::Byte>(0)));
      this->labelTitle->Location = System::Drawing::Point(124, 157);
      this->labelTitle->Name = L"labelTitle";
      this->labelTitle->Size = System::Drawing::Size(152, 25);
      this->labelTitle->TabIndex = 7;
      this->labelTitle->Text = L"Masukan untuk";
      // 
      // registerF
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::FloralWhite;
      this->ClientSize = System::Drawing::Size(784, 441);
      this->Controls->Add(this->btnKembali);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->btnDaftar);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->textBoxPassword);
      this->Controls->Add(this->textBoxUsername);
      this->Controls->Add(this->comboBoxRole);
      this->Controls->Add(this->labelRole);
      this->Controls->Add(this->labelPassword);
      this->Controls->Add(this->labelUsername);
      this->Controls->Add(this->labelTitle);
      this->MaximizeBox = false;
      this->Name = L"registerF";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Register - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &registerF::registerF_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

  }
#pragma endregion

  // ========== Event Handlers (implementations in registrationForm.cpp)
  // ==========
private:
  System::Void registerF_Load(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnKembali_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void btnDaftar_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void comboBoxRole_SelectedIndexChanged(System::Object ^ sender,
                                                 System::EventArgs ^ e);
};
} // namespace ECommerce
