// customerForm.cpp - Implementation of customerForm event handlers
#include "customerForm.h"

namespace ECommerce {

System::Void customerForm::customerForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  // Apply DGV theming
  array<DataGridView ^> ^ grids = {dgvProducts, dgvCart, dgvHistory};
  for each (DataGridView ^ dgv in grids) {
    dgv->BackgroundColor = System::Drawing::Color::White;
    dgv->BorderStyle = System::Windows::Forms::BorderStyle::None;
    dgv->EnableHeadersVisualStyles = false;
    dgv->ColumnHeadersDefaultCellStyle->BackColor =
        System::Drawing::Color::FromArgb(46, 125, 50);
    dgv->ColumnHeadersDefaultCellStyle->ForeColor =
        System::Drawing::Color::White;
    dgv->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
    dgv->DefaultCellStyle->SelectionBackColor =
        System::Drawing::Color::FromArgb(200, 230, 201);
    dgv->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
    dgv->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
    dgv->GridColor = System::Drawing::Color::FromArgb(224, 224, 224);
    dgv->RowTemplate->Height = 32;
    dgv->AlternatingRowsDefaultCellStyle->BackColor =
        System::Drawing::Color::FromArgb(245, 247, 250);
    dgv->ColumnHeadersHeight = 36;
  }

  LoadSaldo();
  LoadCatalog();
  LoadHistory();
  LoadProfile();
  dgvCart->DataSource = cartTable;
  // Hide MerchantID column in cart
  if (dgvCart->Columns["MerchantID"])
    dgvCart->Columns["MerchantID"]->Visible = false;
}

System::Void
customerForm::tabControl_SelectedIndexChanged(System::Object ^ sender,
                                              System::EventArgs ^ e) {
  if (tabControl->SelectedTab == tabHistory) {
    LoadHistory();
  } else if (tabControl->SelectedTab == tabCatalog) {
    LoadCatalog();
    LoadSaldo();
  } else if (tabControl->SelectedTab == tabProfile) {
    LoadProfile();
    LoadSaldo();
  } else if (tabControl->SelectedTab == tabCart) {
    LoadSaldo();
  }
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

void customerForm::FilterProducts(String ^ keyword) {
  DataTable ^ allProducts = DatabaseManager::GetAllProductsWithMerchantName();
  if (String::IsNullOrWhiteSpace(keyword)) {
    dgvProducts->DataSource = allProducts;
  } else {
    DataView ^ dv = gcnew DataView(allProducts);
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
    row["MerchantID"] = Convert::ToInt32(
        dgvProducts->SelectedRows[0]->Cells["MerchantID"]->Value);
    row["Toko"] =
        dgvProducts->SelectedRows[0]->Cells["Toko"]->Value->ToString();
    cartTable->Rows->Add(row);
  }

  UpdateCartTotal();
  nudQuantity->Value = 1;
  // Hide MerchantID column in cart
  if (dgvCart->Columns["MerchantID"])
    dgvCart->Columns["MerchantID"]->Visible = false;
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
  int subtotal = 0;
  int totalItems = 0;
  // Count unique merchants for ongkir
  System::Collections::Generic::List<int> ^ merchantSet =
      gcnew System::Collections::Generic::List<int>();
  for (int i = 0; i < cartTable->Rows->Count; i++) {
    subtotal += Convert::ToInt32(cartTable->Rows[i]["Total"]);
    totalItems += Convert::ToInt32(cartTable->Rows[i]["Jumlah"]);
    int mid = Convert::ToInt32(cartTable->Rows[i]["MerchantID"]);
    if (!merchantSet->Contains(mid))
      merchantSet->Add(mid);
  }
  int ongkir = merchantSet->Count * 10000;
  int grandTotal = subtotal + ongkir;
  lblCartTotal->Text = L"Total: Rp " + String::Format("{0:N0}", grandTotal);
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
  int totalItems = 0;
  System::Collections::Generic::List<int> ^ merchantSet =
      gcnew System::Collections::Generic::List<int>();
  for (int i = 0; i < cartTable->Rows->Count; i++) {
    totalHarga += Convert::ToInt32(cartTable->Rows[i]["Total"]);
    totalItems += Convert::ToInt32(cartTable->Rows[i]["Jumlah"]);
    int mid = Convert::ToInt32(cartTable->Rows[i]["MerchantID"]);
    if (!merchantSet->Contains(mid))
      merchantSet->Add(mid);
  }
  int ongkir = merchantSet->Count * 10000;
  int grandTotal = totalHarga + ongkir;

  // Check saldo (harga + ongkir)
  if (currentSaldo < grandTotal) {
    MessageBox::Show(
        "Saldo tidak cukup!\n\nSubtotal: Rp " +
            String::Format("{0:N0}", totalHarga) + "\nOngkir (" +
            merchantSet->Count + " toko): Rp " +
            String::Format("{0:N0}", ongkir) + "\nTotal: Rp " +
            String::Format("{0:N0}", grandTotal) + "\nSaldo Anda: Rp " +
            String::Format("{0:N0}", currentSaldo),
        "Saldo Tidak Cukup", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Checkout " + cartTable->Rows->Count.ToString() +
                           " item?\n\nSubtotal: Rp " +
                           String::Format("{0:N0}", totalHarga) + "\nOngkir (" +
                           merchantSet->Count + " toko x Rp 10.000): Rp " +
                           String::Format("{0:N0}", ongkir) + "\nTotal: Rp " +
                           String::Format("{0:N0}", grandTotal),
                       "Konfirmasi Checkout", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {

    // Track which merchants have already been charged ongkir
    System::Collections::Generic::List<int> ^ chargedMerchants =
        gcnew System::Collections::Generic::List<int>();

    bool allSuccess = true;
    for (int i = 0; i < cartTable->Rows->Count; i++) {
      int productID = Convert::ToInt32(cartTable->Rows[i]["ID"]);
      int jumlah = Convert::ToInt32(cartTable->Rows[i]["Jumlah"]);
      int merchantID = Convert::ToInt32(cartTable->Rows[i]["MerchantID"]);

      // Purchase each item (jumlah times for multiple quantities)
      for (int j = 0; j < jumlah; j++) {
        // Charge ongkir only on first item of each merchant
        bool chargeOngkir = !chargedMerchants->Contains(merchantID);
        if (!DatabaseManager::PurchaseProduct(productID, currentUserID,
                                              chargeOngkir)) {
          allSuccess = false;
          break;
        }
        if (chargeOngkir)
          chargedMerchants->Add(merchantID);
      }
      if (!allSuccess)
        break;
    }

    if (allSuccess) {
      MessageBox::Show(
          "Checkout berhasil!\n\nSubtotal: Rp " +
              String::Format("{0:N0}", totalHarga) + "\nOngkir: Rp " +
              String::Format("{0:N0}", ongkir) + "\nTotal: Rp " +
              String::Format("{0:N0}", grandTotal) +
              "\n\nPesanan Anda akan segera diproses.",
          "Sukses", MessageBoxButtons::OK, MessageBoxIcon::Information);
      cartTable->Rows->Clear();
      UpdateCartTotal();
      LoadSaldo();
      LoadHistory();
      LoadCatalog();
    } else {
      MessageBox::Show("Gagal melakukan checkout! Stok mungkin habis.", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void customerForm::btnUpdateQuantity_Click(System::Object ^ sender,
                                                   System::EventArgs ^ e) {
  if (dgvCart->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih item yang akan diubah jumlahnya!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int rowIndex = dgvCart->SelectedRows[0]->Index;
  int newJumlah = Convert::ToInt32(nudCartQuantity->Value);
  int productID = Convert::ToInt32(cartTable->Rows[rowIndex]["ID"]);
  int harga = Convert::ToInt32(cartTable->Rows[rowIndex]["Harga"]);

  // Check stock availability
  DataTable ^ products = DatabaseManager::GetAllProductsWithMerchantName();
  for (int i = 0; i < products->Rows->Count; i++) {
    if (Convert::ToInt32(products->Rows[i]["ID"]) == productID) {
      int stok = Convert::ToInt32(products->Rows[i]["Stok"]);
      if (newJumlah > stok) {
        MessageBox::Show(
            "Jumlah melebihi stok! Stok tersedia: " + stok.ToString(),
            "Peringatan", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
      }
      break;
    }
  }

  cartTable->Rows[rowIndex]["Jumlah"] = newJumlah;
  cartTable->Rows[rowIndex]["Total"] = newJumlah * harga;
  UpdateCartTotal();
  MessageBox::Show("Jumlah berhasil diubah!", "Sukses", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
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
  String ^ status =
      dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status != "delivered") {
    MessageBox::Show("Pesanan hanya dapat dikonfirmasi jika sudah dikirim "
                     "(status: delivered)!\n\n"
                     "Status saat ini: " +
                         status,
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
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

System::Void customerForm::btnCancelOrder_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  if (dgvHistory->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan yang ingin dibatalkan!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transactionID =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["ID"]->Value);
  String ^ status =
      dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  // Only allow canceling pending orders
  if (status != "pending") {
    MessageBox::Show(
        "Hanya pesanan dengan status 'pending' yang dapat dibatalkan!\\n\\n" +
            "Status pesanan ini: " + status,
        "Tidak Dapat Dibatalkan", MessageBoxButtons::OK,
        MessageBoxIcon::Warning);
    return;
  }

  int totalPrice =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["Total"]->Value);

  if (MessageBox::Show("Batalkan pesanan ini?\\n\\nTotal: Rp " +
                           String::Format("{0:N0}", totalPrice) +
                           "\\n\\nSaldo Anda akan dikembalikan.",
                       "Konfirmasi Pembatalan", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::CancelOrder(transactionID, currentUserID)) {
      MessageBox::Show("Pesanan berhasil dibatalkan!\\n\\nSaldo Rp " +
                           String::Format("{0:N0}", totalPrice) +
                           " telah dikembalikan ke akun Anda.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadHistory();
      LoadSaldo();
    } else {
      MessageBox::Show("Gagal membatalkan pesanan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

} // namespace ECommerce
