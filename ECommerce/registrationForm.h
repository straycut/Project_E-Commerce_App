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
  System::Windows::Forms::Button ^ btnKembali;

protected:
private:
  System::Windows::Forms::Button ^ btnDaftar;

private:
  System::Windows::Forms::TextBox ^ textBoxPassword;

private:
  System::Windows::Forms::TextBox ^ textBoxUsername;

private:
  System::Windows::Forms::Label ^ labelPassword;

private:
  System::Windows::Forms::Label ^ labelUsername;

private:
  System::Windows::Forms::Label ^ labelTitle;

private:
  System::Windows::Forms::Label ^ labelRole;

private:
  System::Windows::Forms::ComboBox ^ comboBoxRole;

private:
  /// <summary>
  /// Required designer variable.
  /// </summary>
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  void InitializeComponent(void) {
      this->btnKembali = (gcnew System::Windows::Forms::Button());
      this->btnDaftar = (gcnew System::Windows::Forms::Button());
      this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
      this->textBoxUsername = (gcnew System::Windows::Forms::TextBox());
      this->labelPassword = (gcnew System::Windows::Forms::Label());
      this->labelUsername = (gcnew System::Windows::Forms::Label());
      this->labelTitle = (gcnew System::Windows::Forms::Label());
      this->labelRole = (gcnew System::Windows::Forms::Label());
      this->comboBoxRole = (gcnew System::Windows::Forms::ComboBox());
      this->SuspendLayout();
      // 
      // btnKembali
      // 
      this->btnKembali->Location = System::Drawing::Point(104, 290);
      this->btnKembali->Name = L"btnKembali";
      this->btnKembali->Size = System::Drawing::Size(75, 30);
      this->btnKembali->TabIndex = 13;
      this->btnKembali->Text = L"Kembali";
      this->btnKembali->UseVisualStyleBackColor = true;
      this->btnKembali->Click += gcnew System::EventHandler(this, &registerF::btnKembali_Click);
      // 
      // btnDaftar
      // 
      this->btnDaftar->Location = System::Drawing::Point(200, 290);
      this->btnDaftar->Name = L"btnDaftar";
      this->btnDaftar->Size = System::Drawing::Size(75, 30);
      this->btnDaftar->TabIndex = 12;
      this->btnDaftar->Text = L"Daftar";
      this->btnDaftar->UseVisualStyleBackColor = true;
      this->btnDaftar->Click += gcnew System::EventHandler(this, &registerF::btnDaftar_Click);
      // 
      // textBoxPassword
      // 
      this->textBoxPassword->Location = System::Drawing::Point(104, 180);
      this->textBoxPassword->Name = L"textBoxPassword";
      this->textBoxPassword->PasswordChar = '*';
      this->textBoxPassword->Size = System::Drawing::Size(171, 20);
      this->textBoxPassword->TabIndex = 11;
      // 
      // textBoxUsername
      // 
      this->textBoxUsername->Location = System::Drawing::Point(104, 120);
      this->textBoxUsername->Name = L"textBoxUsername";
      this->textBoxUsername->Size = System::Drawing::Size(171, 20);
      this->textBoxUsername->TabIndex = 10;
      // 
      // labelPassword
      // 
      this->labelPassword->AutoSize = true;
      this->labelPassword->Location = System::Drawing::Point(101, 164);
      this->labelPassword->Name = L"labelPassword";
      this->labelPassword->Size = System::Drawing::Size(53, 13);
      this->labelPassword->TabIndex = 9;
      this->labelPassword->Text = L"Password";
      // 
      // labelUsername
      // 
      this->labelUsername->AutoSize = true;
      this->labelUsername->Location = System::Drawing::Point(101, 104);
      this->labelUsername->Name = L"labelUsername";
      this->labelUsername->Size = System::Drawing::Size(55, 13);
      this->labelUsername->TabIndex = 8;
      this->labelUsername->Text = L"Username";
      // 
      // labelTitle
      // 
      this->labelTitle->AutoSize = true;
      this->labelTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
      this->labelTitle->Location = System::Drawing::Point(100, 50);
      this->labelTitle->Name = L"labelTitle";
      this->labelTitle->Size = System::Drawing::Size(204, 24);
      this->labelTitle->TabIndex = 7;
      this->labelTitle->Text = L"Registrasi Akun Baru";
      // 
      // labelRole
      // 
      this->labelRole->AutoSize = true;
      this->labelRole->Location = System::Drawing::Point(101, 220);
      this->labelRole->Name = L"labelRole";
      this->labelRole->Size = System::Drawing::Size(54, 13);
      this->labelRole->TabIndex = 14;
      this->labelRole->Text = L"Pilih Role:";
      // 
      // comboBoxRole
      // 
      this->comboBoxRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->comboBoxRole->FormattingEnabled = true;
      this->comboBoxRole->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Merchant", L"Customer", L"Courier" });
      this->comboBoxRole->Location = System::Drawing::Point(104, 240);
      this->comboBoxRole->Name = L"comboBoxRole";
      this->comboBoxRole->Size = System::Drawing::Size(171, 21);
      this->comboBoxRole->TabIndex = 15;
      this->comboBoxRole->SelectedIndexChanged += gcnew System::EventHandler(this, &registerF::comboBoxRole_SelectedIndexChanged);
      // 
      // registerF
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(384, 360);
      this->Controls->Add(this->comboBoxRole);
      this->Controls->Add(this->labelRole);
      this->Controls->Add(this->btnKembali);
      this->Controls->Add(this->btnDaftar);
      this->Controls->Add(this->textBoxPassword);
      this->Controls->Add(this->textBoxUsername);
      this->Controls->Add(this->labelPassword);
      this->Controls->Add(this->labelUsername);
      this->Controls->Add(this->labelTitle);
      this->Name = L"registerF";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Register - E-Commerce";
      this->Load += gcnew System::EventHandler(this, &registerF::registerF_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

  }
#pragma endregion
private:
  System::Void registerF_Load(System::Object ^ sender, System::EventArgs ^ e) {
    // Set default selection
    comboBoxRole->SelectedIndex = 2; // Default to Customer
  }

private:
  System::Void btnKembali_Click(System::Object ^ sender,
                                System::EventArgs ^ e) {
    // Tutup registration form dan kembali ke login form
    this->Close();
  }

private:
  System::Void btnDaftar_Click(System::Object ^ sender, System::EventArgs ^ e) {
    String ^ username = textBoxUsername->Text;
    String ^ password = textBoxPassword->Text;

    // Validasi input tidak kosong
    if (String::IsNullOrWhiteSpace(username) ||
        String::IsNullOrWhiteSpace(password)) {
      MessageBox::Show("Username dan Password tidak boleh kosong!",
                       "Peringatan", MessageBoxButtons::OK,
                       MessageBoxIcon::Warning);
      return;
    }

    // Validasi role dipilih
    if (comboBoxRole->SelectedIndex < 0) {
      MessageBox::Show("Silakan pilih role!", "Peringatan",
                       MessageBoxButtons::OK, MessageBoxIcon::Warning);
      return;
    }

    String ^ role = comboBoxRole->SelectedItem->ToString();

    // Register user ke database
    if (DatabaseManager::RegisterUser(username, password, role)) {
      MessageBox::Show("Registrasi berhasil! Silakan login.", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      this->Close();
    } else {
      MessageBox::Show("Registrasi gagal. Username mungkin sudah digunakan.",
                       "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
private: System::Void comboBoxRole_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
} // namespace ECommerce
