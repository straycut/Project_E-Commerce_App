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
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->labelNama = (gcnew System::Windows::Forms::Label());
    this->labelSandi = (gcnew System::Windows::Forms::Label());
    this->textBoxNama = (gcnew System::Windows::Forms::TextBox());
    this->textBoxSandi = (gcnew System::Windows::Forms::TextBox());
    this->btnDaftar = (gcnew System::Windows::Forms::Button());
    this->btnMasuk = (gcnew System::Windows::Forms::Button());
    this->SuspendLayout();
    //
    // label1
    //
    this->label1->AutoSize = true;
    this->label1->Font = (gcnew System::Drawing::Font(
        L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
    this->label1->Location = System::Drawing::Point(100, 50);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(180, 24);
    this->label1->TabIndex = 0;
    this->label1->Text = L"Login E-Commerce";
    //
    // labelNama
    //
    this->labelNama->AutoSize = true;
    this->labelNama->Location = System::Drawing::Point(101, 110);
    this->labelNama->Name = L"labelNama";
    this->labelNama->Size = System::Drawing::Size(55, 13);
    this->labelNama->TabIndex = 1;
    this->labelNama->Text = L"Username";
    //
    // labelSandi
    //
    this->labelSandi->AutoSize = true;
    this->labelSandi->Location = System::Drawing::Point(101, 170);
    this->labelSandi->Name = L"labelSandi";
    this->labelSandi->Size = System::Drawing::Size(53, 13);
    this->labelSandi->TabIndex = 2;
    this->labelSandi->Text = L"Password";
    //
    // textBoxNama
    //
    this->textBoxNama->Location = System::Drawing::Point(104, 126);
    this->textBoxNama->Name = L"textBoxNama";
    this->textBoxNama->Size = System::Drawing::Size(171, 20);
    this->textBoxNama->TabIndex = 3;
    //
    // textBoxSandi
    //
    this->textBoxSandi->Location = System::Drawing::Point(104, 186);
    this->textBoxSandi->Name = L"textBoxSandi";
    this->textBoxSandi->PasswordChar = '*';
    this->textBoxSandi->Size = System::Drawing::Size(171, 20);
    this->textBoxSandi->TabIndex = 4;
    //
    // btnDaftar
    //
    this->btnDaftar->Location = System::Drawing::Point(104, 230);
    this->btnDaftar->Name = L"btnDaftar";
    this->btnDaftar->Size = System::Drawing::Size(75, 30);
    this->btnDaftar->TabIndex = 5;
    this->btnDaftar->Text = L"Daftar";
    this->btnDaftar->UseVisualStyleBackColor = true;
    this->btnDaftar->Click +=
        gcnew System::EventHandler(this, &loginF::btnDaftar_Click);
    //
    // btnMasuk
    //
    this->btnMasuk->Location = System::Drawing::Point(200, 230);
    this->btnMasuk->Name = L"btnMasuk";
    this->btnMasuk->Size = System::Drawing::Size(75, 30);
    this->btnMasuk->TabIndex = 6;
    this->btnMasuk->Text = L"Masuk";
    this->btnMasuk->UseVisualStyleBackColor = true;
    this->btnMasuk->Click +=
        gcnew System::EventHandler(this, &loginF::btnMasuk_Click);
    //
    // loginF
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(384, 300);
    this->Controls->Add(this->btnMasuk);
    this->Controls->Add(this->btnDaftar);
    this->Controls->Add(this->textBoxSandi);
    this->Controls->Add(this->textBoxNama);
    this->Controls->Add(this->labelSandi);
    this->Controls->Add(this->labelNama);
    this->Controls->Add(this->label1);
    this->Name = L"loginF";
    this->StartPosition =
        System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Login - E-Commerce";
    this->Load += gcnew System::EventHandler(this, &loginF::loginF_Load);
    this->ResumeLayout(false);
    this->PerformLayout();
  }
#pragma endregion
private:
  System::Void btnDaftar_Click(System::Object ^ sender, System::EventArgs ^ e) {
    // Buat instance dari registrationForm
    ECommerce::registerF ^ registrationForm = gcnew ECommerce::registerF();
    // Tampilkan registration form
    registrationForm->ShowDialog();
    // Tampilkan kembali login form setelah registration form ditutup
    this->Show();
  }

private:
  System::Void btnMasuk_Click(System::Object ^ sender, System::EventArgs ^ e) {
    String ^ username = textBoxNama->Text;
    String ^ password = textBoxSandi->Text;

    // Validasi input tidak kosong
    if (String::IsNullOrWhiteSpace(username) ||
        String::IsNullOrWhiteSpace(password)) {
      MessageBox::Show("Username dan Password tidak boleh kosong!",
                       "Peringatan", MessageBoxButtons::OK,
                       MessageBoxIcon::Warning);
      return;
    }

    // Variabel untuk menyimpan hasil dari database
    String ^ role;
    int userID;
    int saldo;
    int isActive;

    // Validasi user dari database SQLite
    if (DatabaseManager::ValidateUser(username, password, role, userID, saldo,
                                      isActive)) {
      // Check if user is active
      if (isActive == 0) {
        MessageBox::Show("Akun Anda telah dinonaktifkan oleh Admin.\nSilakan "
                         "hubungi Administrator.",
                         "Akun Dinonaktifkan", MessageBoxButtons::OK,
                         MessageBoxIcon::Warning);
        return;
      }

      // Login berhasil, buka form sesuai role
      this->Hide();

      if (role == "Admin") {
        ECommerce::adminForm ^ adminForm = gcnew ECommerce::adminForm();
        adminForm->ShowDialog();
      } else if (role == "Merchant") {
        ECommerce::merchantForm ^ merchantForm =
            gcnew ECommerce::merchantForm();
        merchantForm->ShowDialog();
      } else if (role == "Customer") {
        ECommerce::customerForm ^ customerForm =
            gcnew ECommerce::customerForm();
        customerForm->ShowDialog();
      } else if (role == "Courier") {
        ECommerce::courierForm ^ courierForm = gcnew ECommerce::courierForm();
        courierForm->ShowDialog();
      }

      // Clear fields
      textBoxNama->Text = "";
      textBoxSandi->Text = "";
      this->Show();
    } else {
      MessageBox::Show("Username atau Password salah!", "Login Gagal",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }

private:
  System::Void loginF_Load(System::Object ^ sender, System::EventArgs ^ e) {}
};
} // namespace ECommerce
