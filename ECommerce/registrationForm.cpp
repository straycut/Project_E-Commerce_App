// registrationForm.cpp - Implementation of registrationForm event handlers
#include "registrationForm.h"

namespace ECommerce {

System::Void registerF::registerF_Load(System::Object ^ sender,
                                       System::EventArgs ^ e) {
  // Set default selection
  comboBoxRole->SelectedIndex = 2; // Default to Customer
}

System::Void registerF::btnKembali_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
  // Tutup registration form dan kembali ke login form
  this->Close();
}

System::Void registerF::btnDaftar_Click(System::Object ^ sender,
                                        System::EventArgs ^ e) {
  String ^ username = textBoxUsername->Text;
  String ^ password = textBoxPassword->Text;

  // Validasi input tidak kosong
  if (String::IsNullOrWhiteSpace(username) ||
      String::IsNullOrWhiteSpace(password)) {
    MessageBox::Show("Username dan Password tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  // Validasi role dipilih
  if (comboBoxRole->SelectedIndex < 0) {
    MessageBox::Show("Silakan pilih role!", "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
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

System::Void
registerF::comboBoxRole_SelectedIndexChanged(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  // Empty handler
}

} // namespace ECommerce
