// customerForm.cpp - Implementation of customerForm event handlers
#include "customerForm.h"

namespace ECommerce {

System::Void customerForm::customerForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  LoadSaldo();
  LoadCatalog();
  LoadHistory();
  LoadProfile();
  dgvCart->DataSource = cartTable;
}

void customerForm::LoadCatalog() {
  dgvProducts->DataSource = DatabaseManager::GetAllProductsWithMerchantName();
  // Hide unnecessary columns
  if (dgvProducts->Columns["MerchantID"])
    dgvProducts->Columns["MerchantID"]->Visible = false;
  if (dgvProducts->Columns["Komisi"])
    dgvProducts->Columns["Komisi"]->Visible = false;
}

void customerForm::LoadHistory() {
  dgvHistory->DataSource =
      DatabaseManager::GetTransactionsByCustomer(currentUserID);
}

void customerForm::FilterProducts(String^ keyword) {
  DataTable^ allProducts = DatabaseManager::GetAllProductsWithMerchantName();
  if (String::IsNullOrWhiteSpace(keyword)) {
    dgvProducts->DataSource = allProducts;
  } else {
    DataView^ dv = gcnew DataView(allProducts);
    dv->RowFilter = "Nama LIKE '%" + keyword->Replace("'", "''") + "%'";
    dgvProducts->DataSource = dv;
  }
  // Hide unnecessary columns
  if (dgvProducts->Columns["MerchantID"])
    dgvProducts->Columns["MerchantID"]->Visible = false;
  if (dgvProducts->Columns["Komisi"])
    dgvProducts->Columns["Komisi"]->Visible = false;
}

System::Void customerForm::txtSearch_TextChanged(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  FilterProducts(txtSearch->Text->Trim());
}

void customerForm::LoadSaldo() {
  currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblSaldoInfo->Text = L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
  lblCurrentSaldo->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

System::Void customerForm::btnRefreshCatalog_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  LoadCatalog();
  LoadSaldo();
}

System::Void customerForm::btnAddToCart_Click(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan ditambahkan!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["ID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  int harga =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["Harga"]->Value);
  int stok =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["Stok"]->Value);
  int jumlah = Convert::ToInt32(nudQuantity->Value);

  // Check stock
  if (stok < jumlah) {
    MessageBox::Show("Stok tidak cukup! Stok tersedia: " + stok.ToString(),
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  // Check if product already in cart
  bool found = false;
  for (int i = 0; i < cartTable->Rows->Count; i++) {
    if (Convert::ToInt32(cartTable->Rows[i]["ID"]) == productID) {
      int existingJumlah = Convert::ToInt32(cartTable->Rows[i]["Jumlah"]);
      int newJumlah = existingJumlah + jumlah;
      if (newJumlah > stok) {
        MessageBox::Show(
            "Total jumlah melebihi stok! Stok tersedia: " + stok.ToString(),
            "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
      }
      cartTable->Rows[i]["Jumlah"] = newJumlah;
      cartTable->Rows[i]["Total"] = newJumlah * harga;
      found = true;
      break;
    }
  }

  if (!found) {
    DataRow ^ row = cartTable->NewRow();
    row["ID"] = productID;
    row["Nama"] = productName;
    row["Harga"] = harga;
    row["Jumlah"] = jumlah;
    row["Total"] = harga * jumlah;
    cartTable->Rows->Add(row);
  }

  UpdateCartTotal();
  nudQuantity->Value = 1;
}

System::Void customerForm::btnRemoveFromCart_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  if (dgvCart->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih item yang akan dihapus!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int rowIndex = dgvCart->SelectedRows[0]->Index;
  cartTable->Rows->RemoveAt(rowIndex);
  UpdateCartTotal();
}

void customerForm::UpdateCartTotal() {
  int total = 0;
  for (int i = 0; i < cartTable->Rows->Count; i++) {
    total += Convert::ToInt32(cartTable->Rows[i]["Total"]);
  }
  lblCartTotal->Text = L"Total: Rp " + String::Format("{0:N0}", total);
}

System::Void customerForm::btnCheckout_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (cartTable->Rows->Count == 0) {
    MessageBox::Show("Keranjang masih kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  // Calculate total
  int totalHarga = 0;
  for (int i = 0; i < cartTable->Rows->Count; i++) {
    totalHarga += Convert::ToInt32(cartTable->Rows[i]["Total"]);
  }

  // Check saldo
  if (currentSaldo < totalHarga) {
    MessageBox::Show(
        "Saldo tidak cukup!\n\nTotal: Rp " +
            String::Format("{0:N0}", totalHarga) + "\nSaldo Anda: Rp " +
            String::Format("{0:N0}", currentSaldo),
        "Saldo Tidak Cukup", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Checkout " + cartTable->Rows->Count.ToString() +
                           " item?\n\nTotal: Rp " +
                           String::Format("{0:N0}", totalHarga),
                       "Konfirmasi Checkout", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {

    bool allSuccess = true;
    for (int i = 0; i < cartTable->Rows->Count; i++) {
      int productID = Convert::ToInt32(cartTable->Rows[i]["ID"]);
      int jumlah = Convert::ToInt32(cartTable->Rows[i]["Jumlah"]);

      // Purchase each item (jumlah times for multiple quantities)
      for (int j = 0; j < jumlah; j++) {
        if (!DatabaseManager::PurchaseProduct(productID, currentUserID)) {
          allSuccess = false;
          break;
        }
      }
      if (!allSuccess)
        break;
    }

    if (allSuccess) {
      MessageBox::Show("Checkout berhasil!\n\nTotal: Rp " +
                           String::Format("{0:N0}", totalHarga) +
                           "\n\nPesanan Anda akan segera diproses.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      cartTable->Rows->Clear();
      UpdateCartTotal();
      LoadSaldo();
      LoadHistory();
      LoadCatalog();
    } else {
      MessageBox::Show("Gagal melakukan checkout!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void customerForm::btnRefreshHistory_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  LoadHistory();
}

System::Void customerForm::btnConfirmReceived_Click(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  if (dgvHistory->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan yang akan dikonfirmasi!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transactionID =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["ID"]->Value);
  String ^ status = dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status != "delivered") {
    MessageBox::Show(
        "Pesanan hanya dapat dikonfirmasi jika sudah dikirim (status: delivered)!\n\n"
        "Status saat ini: " + status,
        "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Konfirmasi bahwa pesanan sudah Anda terima?",
                       "Konfirmasi Penerimaan", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {

    if (DatabaseManager::ConfirmDelivery(transactionID, currentUserID)) {
      MessageBox::Show("Pesanan berhasil dikonfirmasi diterima!\n\n"
                       "Terima kasih telah berbelanja.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadHistory();
    } else {
      MessageBox::Show("Gagal mengkonfirmasi pesanan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void customerForm::btnTopUp_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  int amount = 0;
  if (!Int32::TryParse(txtTopUpAmount->Text, amount) || amount <= 0) {
    MessageBox::Show("Masukkan jumlah top up yang valid (angka positif)!",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  if (DatabaseManager::TopUpSaldo(currentUserID, amount)) {
    MessageBox::Show(
        "Top up berhasil!\n\nJumlah: Rp " + String::Format("{0:N0}", amount),
        "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
    LoadSaldo();
    txtTopUpAmount->Text = "";
  } else {
    MessageBox::Show("Gagal melakukan top up!", "Error", MessageBoxButtons::OK,
                     MessageBoxIcon::Error);
  }
}

System::Void customerForm::btnLogout_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  this->Close();
}

void customerForm::LoadProfile() {
  String ^ alamat = DatabaseManager::GetUserAddress(currentUserID);
  txtAlamat->Text = alamat;
}

System::Void customerForm::btnSaveAlamat_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  String ^ alamat = txtAlamat->Text->Trim();

  if (DatabaseManager::UpdateUserAddress(currentUserID, alamat)) {
    MessageBox::Show("Alamat berhasil disimpan!", "Sukses",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
  } else {
    MessageBox::Show("Gagal menyimpan alamat!", "Error", MessageBoxButtons::OK,
                     MessageBoxIcon::Error);
  }
}

} // namespace ECommerce
