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
    dgv->DefaultCellStyle->WrapMode = DataGridViewTriState::True;
    dgv->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
  }

  LoadSaldo();
  LoadCatalog();
  LoadHistory();
  LoadProfile();
  dgvCart->DataSource = cartTable;
  // Hide MerchantID column in cart
  if (dgvCart->Columns["MerchantID"])
    dgvCart->Columns["MerchantID"]->Visible = false;

  // === Dynamic Button: History Tab - Ajukan Refund ===
  btnRequestRefund = gcnew Button();
  btnRequestRefund->Text = L"Ajukan Refund";
  btnRequestRefund->BackColor = System::Drawing::Color::FromArgb(245, 124, 0);
  btnRequestRefund->ForeColor = System::Drawing::Color::White;
  btnRequestRefund->FlatStyle = FlatStyle::Flat;
  btnRequestRefund->FlatAppearance->BorderSize = 0;
  btnRequestRefund->Font = gcnew System::Drawing::Font(
      L"Segoe UI", 9, System::Drawing::FontStyle::Bold);
  btnRequestRefund->Cursor = System::Windows::Forms::Cursors::Hand;
  btnRequestRefund->Size = System::Drawing::Size(120, 30);
  btnRequestRefund->Location =
      System::Drawing::Point(btnCancelOrder->Right + 10, btnCancelOrder->Top);
  btnRequestRefund->Click +=
      gcnew System::EventHandler(this, &customerForm::btnRequestRefund_Click);
  tabHistory->Controls->Add(btnRequestRefund);

  // === Dynamic Button: Beri Rating ===
  btnGiveRating = gcnew Button();
  btnGiveRating->Text = L"Beri Rating";
  btnGiveRating->BackColor = System::Drawing::Color::FromArgb(255, 193, 7);
  btnGiveRating->ForeColor = System::Drawing::Color::Black;
  btnGiveRating->FlatStyle = FlatStyle::Flat;
  btnGiveRating->FlatAppearance->BorderSize = 0;
  btnGiveRating->Font = gcnew System::Drawing::Font(
      L"Segoe UI", 9, System::Drawing::FontStyle::Bold);
  btnGiveRating->Cursor = System::Windows::Forms::Cursors::Hand;
  btnGiveRating->Size = System::Drawing::Size(110, 30);
  btnGiveRating->Location =
      System::Drawing::Point(btnRequestRefund->Right + 10, btnCancelOrder->Top);
  btnGiveRating->Click +=
      gcnew System::EventHandler(this, &customerForm::btnGiveRating_Click);
  tabHistory->Controls->Add(btnGiveRating);

  // === Dynamic Button: Lacak Pesanan ===
  btnTrackOrder = gcnew Button();
  btnTrackOrder->Text = L"Lacak Pesanan";
  btnTrackOrder->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
  btnTrackOrder->ForeColor = System::Drawing::Color::White;
  btnTrackOrder->FlatStyle = FlatStyle::Flat;
  btnTrackOrder->FlatAppearance->BorderSize = 0;
  btnTrackOrder->Font = gcnew System::Drawing::Font(
      L"Segoe UI", 9, System::Drawing::FontStyle::Bold);
  btnTrackOrder->Cursor = System::Windows::Forms::Cursors::Hand;
  btnTrackOrder->Size = System::Drawing::Size(120, 30);
  btnTrackOrder->Location =
      System::Drawing::Point(btnGiveRating->Right + 10, btnCancelOrder->Top);
  btnTrackOrder->Click +=
      gcnew System::EventHandler(this, &customerForm::btnTrackOrder_Click);
  tabHistory->Controls->Add(btnTrackOrder);
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
    // Load address into checkout
    String ^ alamat = DatabaseManager::GetUserAddress(currentUserID);
    txtAlamatCheckout->Text = alamat;
    // Update saldo display
    lblSaldoCheckout->Text =
        L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
    // Update badge
    if (cartTable->Rows->Count > 0)
      tabCart->Text = L"Checkout (" + cartTable->Rows->Count + L")";
    else
      tabCart->Text = L"Checkout";
    UpdateCartTotal();
  }
}

void customerForm::LoadCatalog() {
  dgvProducts->DataSource = DatabaseManager::GetAllProductsWithMerchantName();
  // Hide unnecessary columns
  if (dgvProducts->Columns["MerchantID"])
    dgvProducts->Columns["MerchantID"]->Visible = false;
  if (dgvProducts->Columns["Komisi"])
    dgvProducts->Columns["Komisi"]->Visible = false;
  if (dgvProducts->Columns["_RawID"] != nullptr)
    dgvProducts->Columns["_RawID"]->Visible = false;
}

void customerForm::LoadHistory() {
  dgvHistory->DataSource =
      DatabaseManager::GetTransactionsByCustomer(currentUserID);
  if (dgvHistory->Columns["_RawID"] != nullptr)
    dgvHistory->Columns["_RawID"]->Visible = false;
  if (dgvHistory->Columns["_RawProductID"] != nullptr)
    dgvHistory->Columns["_RawProductID"]->Visible = false;
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
  if (dgvProducts->Columns["_RawID"] != nullptr)
    dgvProducts->Columns["_RawID"]->Visible = false;
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
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
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
  int ongkirRate = rbExpress->Checked ? 20000 : 10000;
  int ongkir = merchantSet->Count * ongkirRate;
  int grandTotal = subtotal + ongkir;
  lblCartTotal->Text = L"Total: Rp " + String::Format("{0:N0}", grandTotal);

  // Update summary panel labels
  lblSubtotal->Text = L"Subtotal: Rp " + String::Format("{0:N0}", subtotal);
  lblOngkir->Text = L"Ongkir (" + merchantSet->Count + L" toko x Rp " +
                    String::Format("{0:N0}", ongkirRate) + L"): Rp " +
                    String::Format("{0:N0}", ongkir);
  lblGrandTotal->Text =
      L"Grand Total: Rp " + String::Format("{0:N0}", grandTotal);
  lblSaldoCheckout->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);

  // Update tab badge
  if (cartTable->Rows->Count > 0)
    tabCart->Text = L"Checkout (" + cartTable->Rows->Count + L")";
  else
    tabCart->Text = L"Checkout";
}

System::Void customerForm::btnCheckout_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (cartTable->Rows->Count == 0) {
    MessageBox::Show("Keranjang masih kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  // Validate address
  if (String::IsNullOrWhiteSpace(txtAlamatCheckout->Text)) {
    MessageBox::Show("Alamat pengiriman harus diisi!\nSilakan isi alamat di "
                     "panel sebelah kanan.",
                     "Alamat Kosong", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    txtAlamatCheckout->Focus();
    return;
  }

  // Validate express courier selection
  bool isExpress = rbExpress->Checked;
  int expressCourierID = 0;
  String ^ shippingType = isExpress ? "express" : "regular";

  if (isExpress) {
    if (cmbExpressCourier->SelectedIndex < 0) {
      MessageBox::Show("Silakan pilih kurir express terlebih dahulu!",
                       "Kurir Express", MessageBoxButtons::OK,
                       MessageBoxIcon::Warning);
      return;
    }
    DataTable ^ courierDt = DatabaseManager::GetExpressCouriers();
    if (cmbExpressCourier->SelectedIndex < courierDt->Rows->Count) {
      expressCourierID = Convert::ToInt32(
          courierDt->Rows[cmbExpressCourier->SelectedIndex]["ID"]);
    }
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
  int ongkirRate = isExpress ? 20000 : 10000;
  int ongkir = merchantSet->Count * ongkirRate;
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

  String ^ pengirimanStr = isExpress ? "Express" : "Regular";
  if (MessageBox::Show("Checkout " + cartTable->Rows->Count.ToString() +
                           " item?\n\nSubtotal: Rp " +
                           String::Format("{0:N0}", totalHarga) + "\nOngkir (" +
                           merchantSet->Count + " toko x Rp " +
                           String::Format("{0:N0}", ongkirRate) + "): Rp " +
                           String::Format("{0:N0}", ongkir) + "\nTotal: Rp " +
                           String::Format("{0:N0}", grandTotal) +
                           "\nPengiriman: " + pengirimanStr,
                       "Konfirmasi Checkout", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {

    // Save address
    DatabaseManager::UpdateUserAddress(currentUserID, txtAlamatCheckout->Text);

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
        bool success;
        if (isExpress && expressCourierID > 0) {
          success = DatabaseManager::PurchaseProduct(productID, currentUserID,
                                                     chargeOngkir, shippingType,
                                                     expressCourierID);
        } else {
          success = DatabaseManager::PurchaseProduct(productID, currentUserID,
                                                     chargeOngkir);
        }
        if (!success) {
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
              String::Format("{0:N0}", grandTotal) + "\nPengiriman: " +
              pengirimanStr + "\n\nPesanan Anda akan segera diproses.",
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
    if (Convert::ToInt32(products->Rows[i]["_RawID"]) == productID) {
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
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["_RawID"]->Value);
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
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["_RawID"]->Value);
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

void customerForm::LoadExpressCouriers() {
  cmbExpressCourier->Items->Clear();
  DataTable ^ dt = DatabaseManager::GetExpressCouriers();
  for (int i = 0; i < dt->Rows->Count; i++) {
    cmbExpressCourier->Items->Add(dt->Rows[i]["Username"]->ToString());
  }
  if (cmbExpressCourier->Items->Count > 0)
    cmbExpressCourier->SelectedIndex = 0;
}

System::Void customerForm::rbExpress_CheckedChanged(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  bool showExpress = rbExpress->Checked;
  lblPilihKurir->Visible = showExpress;
  cmbExpressCourier->Visible = showExpress;
  if (showExpress) {
    LoadExpressCouriers();
  }
  UpdateCartTotal();
}

System::Void customerForm::btnRequestRefund_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  if (dgvHistory->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan yang ingin di-refund!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transactionID =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ status =
      dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status != "shipping") {
    MessageBox::Show(
        "Refund hanya bisa diajukan untuk pesanan dengan status 'shipping'.\n\n"
        "Status pesanan ini: " +
            status,
        "Tidak Dapat Refund", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Ajukan refund untuk pesanan ini?\n\n"
                       "Admin akan memproses permintaan refund Anda.",
                       "Konfirmasi Refund", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::RequestRefund(transactionID, currentUserID)) {
      MessageBox::Show("Permintaan refund berhasil diajukan!\n\n"
                       "Admin akan segera memproses permintaan Anda.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadHistory();
    } else {
      MessageBox::Show("Gagal mengajukan refund!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

// Rating
System::Void customerForm::btnGiveRating_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  if (dgvHistory->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan untuk memberi rating!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transID =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ status =
      dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  if (status != "delivered" && status != "received") {
    MessageBox::Show(
        "Rating hanya bisa diberikan untuk pesanan yang sudah diterima!",
        "Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (DatabaseManager::HasReviewed(transID)) {
    MessageBox::Show("Anda sudah memberikan rating untuk pesanan ini!", "Info",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
    return;
  }

  int productID = Convert::ToInt32(
      dgvHistory->SelectedRows[0]->Cells["_RawProductID"]->Value);

  // Rating dialog
  Form ^ dialog = gcnew Form();
  dialog->Text = L"Beri Rating";
  dialog->Size = System::Drawing::Size(350, 250);
  dialog->StartPosition = FormStartPosition::CenterParent;
  dialog->FormBorderStyle =
      System::Windows::Forms::FormBorderStyle::FixedDialog;
  dialog->MaximizeBox = false;
  dialog->MinimizeBox = false;

  Label ^ lblRate = gcnew Label();
  lblRate->Text = L"Rating (1-5 bintang):";
  lblRate->Location = System::Drawing::Point(15, 15);
  lblRate->AutoSize = true;
  dialog->Controls->Add(lblRate);

  NumericUpDown ^ nudRating = gcnew NumericUpDown();
  nudRating->Minimum = 1;
  nudRating->Maximum = 5;
  nudRating->Value = 5;
  nudRating->Location = System::Drawing::Point(15, 40);
  nudRating->Size = System::Drawing::Size(60, 25);
  dialog->Controls->Add(nudRating);

  Label ^ lblComment = gcnew Label();
  lblComment->Text = L"Komentar:";
  lblComment->Location = System::Drawing::Point(15, 75);
  lblComment->AutoSize = true;
  dialog->Controls->Add(lblComment);

  TextBox ^ txtComment = gcnew TextBox();
  txtComment->Multiline = true;
  txtComment->Location = System::Drawing::Point(15, 95);
  txtComment->Size = System::Drawing::Size(300, 60);
  dialog->Controls->Add(txtComment);

  Button ^ btnOK = gcnew Button();
  btnOK->Text = L"Kirim Rating";
  btnOK->BackColor = System::Drawing::Color::FromArgb(255, 193, 7);
  btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
  btnOK->Location = System::Drawing::Point(15, 170);
  btnOK->Size = System::Drawing::Size(120, 30);
  dialog->Controls->Add(btnOK);

  Button ^ btnCancel = gcnew Button();
  btnCancel->Text = L"Batal";
  btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  btnCancel->Location = System::Drawing::Point(150, 170);
  btnCancel->Size = System::Drawing::Size(100, 30);
  dialog->Controls->Add(btnCancel);

  dialog->AcceptButton = btnOK;
  dialog->CancelButton = btnCancel;

  if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
    int rating = Convert::ToInt32(nudRating->Value);
    if (DatabaseManager::AddReview(transID, currentUserID, productID, rating,
                                   txtComment->Text)) {
      MessageBox::Show("Rating berhasil dikirim! Terima kasih.", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
    } else {
      MessageBox::Show("Gagal mengirim rating!", "Error", MessageBoxButtons::OK,
                       MessageBoxIcon::Error);
    }
  }
}

// Tracking
System::Void customerForm::btnTrackOrder_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  if (dgvHistory->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih pesanan untuk melacak!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int transID =
      Convert::ToInt32(dgvHistory->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ status =
      dgvHistory->SelectedRows[0]->Cells["Status"]->Value->ToString();

  DataTable ^ tracking = DatabaseManager::GetOrderTracking(transID);

  // Dialog with DataGridView
  Form ^ dialog = gcnew Form();
  dialog->Text = L"Lacak Pesanan #" + transID;
  dialog->Size = System::Drawing::Size(500, 350);
  dialog->StartPosition = FormStartPosition::CenterParent;
  dialog->FormBorderStyle =
      System::Windows::Forms::FormBorderStyle::FixedDialog;
  dialog->MaximizeBox = false;
  dialog->MinimizeBox = false;

  Label ^ lblStatus = gcnew Label();
  lblStatus->Text = L"Status saat ini: " + status;
  lblStatus->Font = gcnew System::Drawing::Font(
      L"Segoe UI", 12, System::Drawing::FontStyle::Bold);
  lblStatus->Location = System::Drawing::Point(15, 15);
  lblStatus->AutoSize = true;
  dialog->Controls->Add(lblStatus);

  if (tracking->Rows->Count == 0) {
    Label ^ lblEmpty = gcnew Label();
    lblEmpty->Text = L"Belum ada data pelacakan untuk pesanan ini.";
    lblEmpty->Location = System::Drawing::Point(15, 50);
    lblEmpty->AutoSize = true;
    dialog->Controls->Add(lblEmpty);
  } else {
    DataGridView ^ dgv = gcnew DataGridView();
    dgv->DataSource = tracking;
    dgv->Location = System::Drawing::Point(15, 50);
    dgv->Size = System::Drawing::Size(455, 230);
    dgv->AllowUserToAddRows = false;
    dgv->ReadOnly = true;
    dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
    dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
    dgv->BackgroundColor = System::Drawing::Color::White;
    dialog->Controls->Add(dgv);
  }

  Button ^ btnClose = gcnew Button();
  btnClose->Text = L"Tutup";
  btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  btnClose->Location = System::Drawing::Point(15, 285);
  btnClose->Size = System::Drawing::Size(100, 30);
  dialog->Controls->Add(btnClose);
  dialog->CancelButton = btnClose;

  dialog->ShowDialog();
}

} // namespace ECommerce
