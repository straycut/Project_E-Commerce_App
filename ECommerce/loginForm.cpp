// loginForm.cpp - Implementation of loginForm event handlers
#include "loginForm.h"

namespace ECommerce {

System::Void loginF::btnDaftar_Click(System::Object ^ sender,
                                     System::EventArgs ^ e) {
  // Buat instance dari registrationForm
  ECommerce::registerF ^ registrationForm = gcnew ECommerce::registerF();
  // Tampilkan registration form
  registrationForm->ShowDialog();
  // Tampilkan kembali login form setelah registration form ditutup
  this->Show();
}

System::Void loginF::btnMasuk_Click(System::Object ^ sender,
                                    System::EventArgs ^ e) {
  String ^ username = textBoxNama->Text;
  String ^ password = textBoxSandi->Text;

  // Validasi input tidak kosong
  if (String::IsNullOrWhiteSpace(username) ||
      String::IsNullOrWhiteSpace(password)) {
    MessageBox::Show("Username dan Password tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
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
      ECommerce::adminForm ^ adminF = gcnew ECommerce::adminForm();
      adminF->ShowDialog();
    } else if (role == "Merchant") {
      ECommerce::merchantForm ^ merchantF =
          gcnew ECommerce::merchantForm(userID, username);
      merchantF->ShowDialog();
    } else if (role == "Customer") {
      ECommerce::customerForm ^ customerF =
          gcnew ECommerce::customerForm(userID, username);
      customerF->ShowDialog();
    } else if (role == "Courier") {
      ECommerce::courierForm ^ courierF =
          gcnew ECommerce::courierForm(userID, username);
      courierF->ShowDialog();
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

System::Void loginF::loginF_Load(System::Object ^ sender,
                                 System::EventArgs ^ e) {
  // Empty handler
}

} // namespace ECommerce
