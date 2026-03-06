// merchantForm.cpp - Implementation of merchantForm event handlers
#include "merchantForm.h"

namespace ECommerce {

System::Void merchantForm::merchantForm_Load(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  isEditMode = false;
  editProductID = 0;

  // Apply DGV theming
  array<DataGridView ^> ^ grids = {dgvProducts};
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

  LoadDashboard();
  LoadProducts();
  LoadSales();
  LoadProfile();

  // === Dynamic Tab: Notifikasi ===
  tabNotifikasi = gcnew TabPage();
  tabNotifikasi->Text = L"Notifikasi";
  tabNotifikasi->UseVisualStyleBackColor = true;

  dgvNotifikasi = gcnew DataGridView();
  dgvNotifikasi->Location = System::Drawing::Point(10, 15);
  dgvNotifikasi->Size = System::Drawing::Size(832, 420);
  dgvNotifikasi->AllowUserToAddRows = false;
  dgvNotifikasi->AllowUserToDeleteRows = false;
  dgvNotifikasi->ReadOnly = true;
  dgvNotifikasi->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
  dgvNotifikasi->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
  dgvNotifikasi->BackgroundColor = System::Drawing::Color::White;
  dgvNotifikasi->BorderStyle = System::Windows::Forms::BorderStyle::None;
  dgvNotifikasi->EnableHeadersVisualStyles = false;
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->BackColor =
      System::Drawing::Color::FromArgb(46, 125, 50);
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->ForeColor =
      System::Drawing::Color::White;
  dgvNotifikasi->ColumnHeadersDefaultCellStyle->Font =
      gcnew System::Drawing::Font(L"Segoe UI", 10,
                                  System::Drawing::FontStyle::Bold);
  dgvNotifikasi->DefaultCellStyle->Font =
      gcnew System::Drawing::Font(L"Segoe UI", 9);
  dgvNotifikasi->DefaultCellStyle->WrapMode = DataGridViewTriState::True;
  dgvNotifikasi->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
  dgvNotifikasi->ColumnHeadersHeight = 36;
  dgvNotifikasi->RowTemplate->Height = 32;

  tabNotifikasi->Controls->Add(dgvNotifikasi);
  tabControl->Controls->Add(tabNotifikasi);

  LoadNotifikasi();

  // Auto-switch to notification tab if there are unread notifications
  int unreadCount = DatabaseManager::GetUnreadNotificationCount(currentUserID);
  if (unreadCount > 0) {
    tabControl->SelectedTab = tabNotifikasi;
    DatabaseManager::MarkNotificationsRead(currentUserID);
    tabNotifikasi->Text = L"Notifikasi";
  }
}

void merchantForm::LoadDashboard() {
  array<int> ^ stats = DatabaseManager::GetMerchantStats(currentUserID);
  lblTotalProducts->Text = L"Total Produk: " + stats[0];
  lblTotalSales->Text = L"Total Penjualan: " + stats[1];
  lblTotalIncome->Text =
      L"Pendapatan: Rp " + String::Format("{0:N0}", stats[2]);

  // Display current balance
  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblCurrentBalance->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

void merchantForm::LoadProfile() {
  String ^ alamat = DatabaseManager::GetUserAddress(currentUserID);
  txtAlamatToko->Text = alamat;
}

void merchantForm::LoadProducts() {
  dgvProducts->DataSource =
      DatabaseManager::GetProductsByMerchant(currentUserID);
  if (dgvProducts->Columns["_RawID"] != nullptr)
    dgvProducts->Columns["_RawID"]->Visible = false;
}

void merchantForm::LoadSales() {
  DataTable ^ dt = DatabaseManager::GetTransactionsByMerchant(currentUserID);

  flpSales->Controls->Clear();

  if (dt->Rows->Count == 0) {
    Label ^ lblEmpty = gcnew Label();
    lblEmpty->Text = L"Belum ada riwayat penjualan.";
    lblEmpty->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
    lblEmpty->ForeColor = System::Drawing::Color::Gray;
    lblEmpty->AutoSize = true;
    lblEmpty->Padding = System::Windows::Forms::Padding(10, 20, 0, 0);
    flpSales->Controls->Add(lblEmpty);
    return;
  }

  int cardWidth = flpSales->Width - 30;

  // Group by Pembeli
  System::Collections::Generic::Dictionary<
      String ^, System::Collections::Generic::List<int> ^> ^
      groups =
      gcnew System::Collections::Generic::Dictionary<
          String ^, System::Collections::Generic::List<int> ^>();
  System::Collections::Generic::List<String ^> ^ groupOrder =
      gcnew System::Collections::Generic::List<String ^>();

  for (int i = 0; i < dt->Rows->Count; i++) {
    String ^ customer = dt->Rows[i]["Pembeli"]->ToString();
    if (!groups->ContainsKey(customer)) {
      groups[customer] = gcnew System::Collections::Generic::List<int>();
      groupOrder->Add(customer);
    }
    groups[customer]->Add(i);
  }

  for (int g = 0; g < groupOrder->Count; g++) {
    String ^ customer = groupOrder[g];
    System::Collections::Generic::List<int> ^ rowIndices = groups[customer];
    int itemCount = rowIndices->Count;

    // === Card Panel ===
    Panel ^ card = gcnew Panel();
    card->Width = cardWidth;
    card->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    card->BackColor = System::Drawing::Color::White;
    card->Margin = System::Windows::Forms::Padding(3, 3, 3, 8);

    int yPos = 0;

    // === Header bar ===
    String ^ alamatPembeli =
        dt->Rows[rowIndices[0]]["Alamat Pembeli"]->ToString();

    Panel ^ header = gcnew Panel();
    header->Dock = DockStyle::Top;
    header->Height = 42;
    header->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);

    Label ^ lblCustName = gcnew Label();
    lblCustName->Text =
        L"Pembeli: " + customer + L" (" + itemCount + L" pesanan)";
    lblCustName->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold);
    lblCustName->ForeColor = System::Drawing::Color::White;
    lblCustName->Location = System::Drawing::Point(10, 2);
    lblCustName->AutoSize = true;
    header->Controls->Add(lblCustName);

    Label ^ lblAddr = gcnew Label();
    lblAddr->Text = alamatPembeli;
    lblAddr->Font = gcnew System::Drawing::Font(L"Segoe UI", 8);
    lblAddr->ForeColor = System::Drawing::Color::FromArgb(200, 230, 201);
    lblAddr->Location = System::Drawing::Point(10, 22);
    lblAddr->AutoSize = true;
    header->Controls->Add(lblAddr);

    card->Controls->Add(header);
    yPos = 48;

    // Calculate group total
    int groupTotal = 0;
    for (int r = 0; r < rowIndices->Count; r++) {
      groupTotal += Convert::ToInt32(dt->Rows[rowIndices[r]]["Harga"]);
    }

    // === Item rows (26px each) ===
    for (int r = 0; r < rowIndices->Count; r++) {
      int idx = rowIndices[r];
      String ^ produk = dt->Rows[idx]["Produk"]->ToString();
      int harga = Convert::ToInt32(dt->Rows[idx]["Harga"]);

      Panel ^ itemRow = gcnew Panel();
      itemRow->Location = System::Drawing::Point(0, yPos);
      itemRow->Size = System::Drawing::Size(cardWidth - 2, 26);
      if (r % 2 == 1)
        itemRow->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);

      Label ^ lblProd = gcnew Label();
      lblProd->Text = L"  \x2022 " + produk;
      lblProd->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblProd->Location = System::Drawing::Point(8, 4);
      lblProd->AutoSize = true;
      itemRow->Controls->Add(lblProd);

      Label ^ lblPrice = gcnew Label();
      lblPrice->Text = L"Rp " + String::Format("{0:N0}", harga);
      lblPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblPrice->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
      lblPrice->Location = System::Drawing::Point(cardWidth - 150, 4);
      lblPrice->AutoSize = true;
      itemRow->Controls->Add(lblPrice);

      card->Controls->Add(itemRow);
      yPos += 26;
    }

    // === Footer ===
    Panel ^ footer = gcnew Panel();
    footer->Location = System::Drawing::Point(0, yPos);
    footer->Size = System::Drawing::Size(cardWidth - 2, 40);
    footer->BackColor = System::Drawing::Color::FromArgb(245, 245, 245);

    Label ^ lblTotal = gcnew Label();
    lblTotal->Text = L"Total: Rp " + String::Format("{0:N0}", groupTotal);
    lblTotal->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
    lblTotal->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
    lblTotal->Location = System::Drawing::Point(10, 10);
    lblTotal->AutoSize = true;
    footer->Controls->Add(lblTotal);

    card->Controls->Add(footer);
    yPos += 40;

    card->Height = yPos;
    flpSales->Controls->Add(card);
  }
}

void merchantForm::ClearProductForm() {
  txtNamaProduk->Text = "";
  txtHarga->Text = "";
  txtKomisi->Text = "5";
  txtStok->Text = "0";
  txtKategori->Text = "";
  txtDeskripsi->Text = "";
  isEditMode = false;
  editProductID = 0;
  panelProduct->Visible = false;
}

System::Void merchantForm::btnSaveAlamat_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  String ^ alamat = txtAlamatToko->Text->Trim();

  if (DatabaseManager::UpdateUserAddress(currentUserID, alamat)) {
    MessageBox::Show("Lokasi toko berhasil disimpan!", "Sukses",
                     MessageBoxButtons::OK, MessageBoxIcon::Information);
  } else {
    MessageBox::Show("Gagal menyimpan lokasi toko!", "Error",
                     MessageBoxButtons::OK, MessageBoxIcon::Error);
  }
}

System::Void merchantForm::btnRefreshDashboard_Click(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  LoadDashboard();
  MessageBox::Show("Dashboard diperbarui!", "Info", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
}

System::Void merchantForm::btnRefreshProducts_Click(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  LoadProducts();
}

System::Void merchantForm::btnAddProduct_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  isEditMode = false;
  editProductID = 0;
  txtNamaProduk->Text = "";
  txtHarga->Text = "";
  txtKomisi->Text = "5";
  txtStok->Text = "0";
  txtKategori->Text = "";
  txtDeskripsi->Text = "";
  panelProduct->Visible = true;
  txtNamaProduk->Focus();
}

System::Void merchantForm::btnEditProduct_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan diedit!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  isEditMode = true;
  editProductID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  txtNamaProduk->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtHarga->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  // Komisi is fixed at 5%, no need to read from grid
  txtKomisi->Text = "5";
  txtStok->Text =
      dgvProducts->SelectedRows[0]->Cells["Stok"]->Value->ToString();
  txtKategori->Text =
      dgvProducts->SelectedRows[0]->Cells["Kategori"]->Value->ToString();
  txtDeskripsi->Text =
      dgvProducts->SelectedRows[0]->Cells["Deskripsi"]->Value->ToString();
  panelProduct->Visible = true;
  txtNamaProduk->Focus();
}

System::Void merchantForm::btnDeleteProduct_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk yang akan dihapus!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int productID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  String ^ productName =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();

  if (MessageBox::Show("Apakah Anda yakin ingin menghapus produk '" +
                           productName + "'?",
                       "Konfirmasi Hapus", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::DeleteProduct(productID)) {
      MessageBox::Show("Produk berhasil dihapus!", "Sukses",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
      LoadProducts();
      LoadDashboard();
    } else {
      MessageBox::Show("Gagal menghapus produk!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

System::Void merchantForm::btnSaveProduct_Click(System::Object ^ sender,
                                                System::EventArgs ^ e) {
  // Validasi input
  if (String::IsNullOrWhiteSpace(txtNamaProduk->Text)) {
    MessageBox::Show("Nama produk tidak boleh kosong!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int harga = 0;
  int komisi = 5; // Fixed 5% commission

  if (!Int32::TryParse(txtHarga->Text, harga) || harga <= 0) {
    MessageBox::Show("Harga harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  int stok = 0;
  if (!Int32::TryParse(txtStok->Text, stok) || stok < 0) {
    MessageBox::Show("Stok harus berupa angka positif!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  bool success = false;

  if (isEditMode) {
    success = DatabaseManager::UpdateProduct(
        editProductID, txtNamaProduk->Text, harga, komisi, stok,
        txtKategori->Text, txtDeskripsi->Text);
  } else {
    success = DatabaseManager::AddProduct(
        txtNamaProduk->Text, harga, komisi, stok, currentUserID,
        txtKategori->Text, txtDeskripsi->Text);
  }

  if (success) {
    MessageBox::Show(isEditMode ? "Produk berhasil diperbarui!"
                                : "Produk berhasil ditambahkan!",
                     "Sukses", MessageBoxButtons::OK,
                     MessageBoxIcon::Information);
    ClearProductForm();
    LoadProducts();
    LoadDashboard();
  } else {
    MessageBox::Show("Gagal menyimpan produk!", "Error", MessageBoxButtons::OK,
                     MessageBoxIcon::Error);
  }
}

System::Void merchantForm::btnCancelProduct_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  ClearProductForm();
}

System::Void merchantForm::btnRefreshSales_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  LoadSales();
}

System::Void merchantForm::btnLogout_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  this->Close();
}

System::Void merchantForm::btnAddStock_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  if (dgvProducts->SelectedRows->Count == 0) {
    MessageBox::Show("Pilih produk untuk menambah stok!", "Peringatan",
                     MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  isEditMode = true;
  editProductID =
      Convert::ToInt32(dgvProducts->SelectedRows[0]->Cells["_RawID"]->Value);
  txtNamaProduk->Text =
      dgvProducts->SelectedRows[0]->Cells["Nama"]->Value->ToString();
  txtHarga->Text =
      dgvProducts->SelectedRows[0]->Cells["Harga"]->Value->ToString();
  // Komisi is fixed at 5%, no need to read from grid
  txtKomisi->Text = "5";
  txtStok->Text =
      dgvProducts->SelectedRows[0]->Cells["Stok"]->Value->ToString();
  txtKategori->Text =
      dgvProducts->SelectedRows[0]->Cells["Kategori"]->Value->ToString();
  txtDeskripsi->Text =
      dgvProducts->SelectedRows[0]->Cells["Deskripsi"]->Value->ToString();
  panelProduct->Visible = true;
  txtStok->Focus();
  txtStok->SelectAll();
}

System::Void merchantForm::btnWithdraw_Click(System::Object ^ sender,
                                             System::EventArgs ^ e) {
  int amount = 0;
  if (!Int32::TryParse(txtWithdrawAmount->Text, amount) || amount <= 0) {
    MessageBox::Show("Masukkan jumlah penarikan yang valid (angka positif)!",
                     "Peringatan", MessageBoxButtons::OK,
                     MessageBoxIcon::Warning);
    return;
  }

  // Check current balance
  int currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  if (amount > currentSaldo) {
    MessageBox::Show(
        "Saldo tidak cukup!\\n\\nJumlah penarikan: Rp " +
            String::Format("{0:N0}", amount) + "\\nSaldo Anda: Rp " +
            String::Format("{0:N0}", currentSaldo),
        "Saldo Tidak Cukup", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    return;
  }

  if (MessageBox::Show("Tarik saldo sebesar Rp " +
                           String::Format("{0:N0}", amount) + "?",
                       "Konfirmasi Penarikan", MessageBoxButtons::YesNo,
                       MessageBoxIcon::Question) ==
      System::Windows::Forms::DialogResult::Yes) {
    if (DatabaseManager::WithdrawSaldo(currentUserID, amount)) {
      MessageBox::Show("Penarikan berhasil!\\n\\nJumlah: Rp " +
                           String::Format("{0:N0}", amount) +
                           "\\n\\nSaldo akan ditransfer ke rekening Anda.",
                       "Sukses", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadDashboard();
      txtWithdrawAmount->Text = "";
    } else {
      MessageBox::Show("Gagal melakukan penarikan!", "Error",
                       MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  }
}

void merchantForm::LoadNotifikasi() {
  DataTable ^ dt = DatabaseManager::GetNotifications(currentUserID);
  dgvNotifikasi->DataSource = dt;

  int unread = DatabaseManager::GetUnreadNotificationCount(currentUserID);
  if (unread > 0) {
    tabNotifikasi->Text = L"Notifikasi (" + unread + L")";
  } else {
    tabNotifikasi->Text = L"Notifikasi";
  }
}

} // namespace ECommerce
