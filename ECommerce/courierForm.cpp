// courierForm.cpp - Implementation of courierForm event handlers
#include "courierForm.h"

namespace ECommerce {

System::Void courierForm::courierForm_Load(System::Object ^ sender,
                                           System::EventArgs ^ e) {
  // Hide old DataGridViews and buttons
  dgvPending->Visible = false;
  dgvActive->Visible = false;
  dgvHistory->Visible = false;
  btnClaim->Visible = false;
  btnComplete->Visible = false;
  btnRefreshPending->Visible = false;
  btnRefreshActive->Visible = false;
  btnRefreshHistory->Visible = false;

  // Create FlowLayoutPanels for grouped cards
  flowPending = gcnew FlowLayoutPanel();
  flowPending->Location = System::Drawing::Point(10, 55);
  flowPending->Size = System::Drawing::Size(832, 390);
  flowPending->AutoScroll = true;
  flowPending->FlowDirection = FlowDirection::TopDown;
  flowPending->WrapContents = false;
  flowPending->BackColor = System::Drawing::Color::Transparent;
  tabPending->Controls->Add(flowPending);

  flowActive = gcnew FlowLayoutPanel();
  flowActive->Location = System::Drawing::Point(10, 55);
  flowActive->Size = System::Drawing::Size(832, 390);
  flowActive->AutoScroll = true;
  flowActive->FlowDirection = FlowDirection::TopDown;
  flowActive->WrapContents = false;
  flowActive->BackColor = System::Drawing::Color::Transparent;
  tabActive->Controls->Add(flowActive);

  flowHistory = gcnew FlowLayoutPanel();
  flowHistory->Location = System::Drawing::Point(10, 55);
  flowHistory->Size = System::Drawing::Size(832, 390);
  flowHistory->AutoScroll = true;
  flowHistory->FlowDirection = FlowDirection::TopDown;
  flowHistory->WrapContents = false;
  flowHistory->BackColor = System::Drawing::Color::Transparent;
  tabHistory->Controls->Add(flowHistory);

  LoadDashboard();
  LoadPending();
  LoadActive();
  LoadHistory();

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
}

void courierForm::LoadDashboard() {
  array<int> ^ stats = DatabaseManager::GetCourierStats(currentUserID);
  lblTodayDeliveries->Text = L"Pengiriman Hari Ini: " + stats[0];
  lblTotalDeliveries->Text = L"Total Pengiriman: " + stats[1];
  lblTotalIncome->Text =
      L"Pendapatan: Rp " + String::Format("{0:N0}", stats[2]);

  currentSaldo = DatabaseManager::GetUserSaldo(currentUserID);
  lblCurrentBalance->Text =
      L"Saldo: Rp " + String::Format("{0:N0}", currentSaldo);
}

void courierForm::LoadPending() {
  String ^ courierType = DatabaseManager::GetUserCourierType(currentUserID);
  DataTable ^ dt =
      DatabaseManager::GetPendingDeliveries(currentUserID, courierType);
  // actionMode 1 = claim (Ambil Pesanan)
  RenderGroupedCards(flowPending, dt, L"Ambil Pesanan", 1);
}

void courierForm::LoadActive() {
  DataTable ^ dt = DatabaseManager::GetActiveDeliveries(currentUserID);
  // actionMode 2 = complete (Selesai Kirim)
  RenderGroupedCards(flowActive, dt, L"Selesai Kirim", 2);
}

void courierForm::LoadHistory() {
  DataTable ^ dt = DatabaseManager::GetDeliveryHistory(currentUserID);
  // actionMode 0 = no action (history only)
  RenderGroupedCards(flowHistory, dt, nullptr, 0);
}

void courierForm::RenderGroupedCards(FlowLayoutPanel ^ flow, DataTable ^ dt,
                                     String ^ actionText, int actionMode) {
  flow->Controls->Clear();

  if (dt->Rows->Count == 0) {
    Label ^ lblEmpty = gcnew Label();
    lblEmpty->Text = L"Tidak ada pesanan.";
    lblEmpty->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
    lblEmpty->ForeColor = System::Drawing::Color::Gray;
    lblEmpty->AutoSize = true;
    lblEmpty->Padding = System::Windows::Forms::Padding(10, 20, 0, 0);
    flow->Controls->Add(lblEmpty);
    return;
  }

  // Group rows by CustomerID
  System::Collections::Generic::Dictionary<
      int, System::Collections::Generic::List<int> ^> ^
      groups =
      gcnew System::Collections::Generic::Dictionary<
          int, System::Collections::Generic::List<int> ^>();
  System::Collections::Generic::List<int> ^ groupOrder =
      gcnew System::Collections::Generic::List<int>();

  for (int i = 0; i < dt->Rows->Count; i++) {
    int custID = Convert::ToInt32(dt->Rows[i]["CustomerID"]);
    if (!groups->ContainsKey(custID)) {
      groups[custID] = gcnew System::Collections::Generic::List<int>();
      groupOrder->Add(custID);
    }
    groups[custID]->Add(i);
  }

  int cardWidth = flow->Width - 30;

  for (int g = 0; g < groupOrder->Count; g++) {
    int custID = groupOrder[g];
    System::Collections::Generic::List<int> ^ rowIndices = groups[custID];
    int firstIdx = rowIndices[0];

    String ^ customerName = dt->Rows[firstIdx]["Pembeli"]->ToString();
    String ^ customerAddr = dt->Rows[firstIdx]["Alamat Customer"]->ToString();
    int itemCount = rowIndices->Count;

    // Calculate total price for this group
    int groupTotal = 0;
    for (int r = 0; r < rowIndices->Count; r++) {
      groupTotal += Convert::ToInt32(dt->Rows[rowIndices[r]]["Harga"]);
    }

    // === Card Panel ===
    Panel ^ card = gcnew Panel();
    card->Width = cardWidth;
    card->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    card->BackColor = System::Drawing::Color::White;
    card->Margin = System::Windows::Forms::Padding(3, 3, 3, 8);

    int yPos = 0;

    // === Header bar ===
    Panel ^ header = gcnew Panel();
    header->Dock = DockStyle::Top;
    header->Height = 42;
    header->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);

    Label ^ lblCustName = gcnew Label();
    lblCustName->Text = customerName + L" (" + itemCount + L" item)";
    lblCustName->Font = gcnew System::Drawing::Font(
        L"Segoe UI", 11, System::Drawing::FontStyle::Bold);
    lblCustName->ForeColor = System::Drawing::Color::White;
    lblCustName->Location = System::Drawing::Point(10, 2);
    lblCustName->AutoSize = true;
    header->Controls->Add(lblCustName);

    Label ^ lblAddr = gcnew Label();
    lblAddr->Text = customerAddr;
    lblAddr->Font = gcnew System::Drawing::Font(L"Segoe UI", 8);
    lblAddr->ForeColor = System::Drawing::Color::FromArgb(200, 230, 201);
    lblAddr->Location = System::Drawing::Point(10, 22);
    lblAddr->AutoSize = true;
    header->Controls->Add(lblAddr);

    card->Controls->Add(header);
    yPos = 48;

    // === Product list ===
    for (int r = 0; r < rowIndices->Count; r++) {
      int idx = rowIndices[r];
      String ^ prodName = dt->Rows[idx]["Produk"]->ToString();
      int prodPrice = Convert::ToInt32(dt->Rows[idx]["Harga"]);

      Panel ^ itemRow = gcnew Panel();
      itemRow->Location = System::Drawing::Point(0, yPos);
      itemRow->Size = System::Drawing::Size(cardWidth - 2, 26);
      if (r % 2 == 1)
        itemRow->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);

      Label ^ lblProd = gcnew Label();
      lblProd->Text = L"  \x2022 " + prodName;
      lblProd->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblProd->Location = System::Drawing::Point(8, 4);
      lblProd->AutoSize = true;
      itemRow->Controls->Add(lblProd);

      Label ^ lblPrice = gcnew Label();
      lblPrice->Text = L"Rp " + String::Format("{0:N0}", prodPrice);
      lblPrice->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
      lblPrice->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
      lblPrice->Location = System::Drawing::Point(cardWidth - 150, 4);
      lblPrice->AutoSize = true;
      itemRow->Controls->Add(lblPrice);

      card->Controls->Add(itemRow);
      yPos += 26;
    }

    // === Footer: total + action button ===
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

    if (actionMode > 0 && actionText != nullptr) {
      Button ^ btnAction = gcnew Button();
      btnAction->Text = actionText;
      btnAction->Font = gcnew System::Drawing::Font(
          L"Segoe UI", 9, System::Drawing::FontStyle::Bold);
      btnAction->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);
      btnAction->ForeColor = System::Drawing::Color::White;
      btnAction->FlatStyle = FlatStyle::Flat;
      btnAction->FlatAppearance->BorderSize = 0;
      btnAction->Cursor = System::Windows::Forms::Cursors::Hand;
      btnAction->Size = System::Drawing::Size(140, 30);
      btnAction->Location = System::Drawing::Point(cardWidth - 160, 5);

      // Store customer ID and action mode in Tag
      // Format: "actionMode|custID|transID1,transID2,..."
      String ^ transIDs = "";
      for (int r = 0; r < rowIndices->Count; r++) {
        if (r > 0)
          transIDs += ",";
        transIDs += dt->Rows[rowIndices[r]]["_RawID"]->ToString();
      }
      btnAction->Tag = actionMode + "|" + custID + "|" + transIDs;
      btnAction->Click +=
          gcnew System::EventHandler(this, &courierForm::btnGroupAction_Click);

      footer->Controls->Add(btnAction);
    }

    card->Controls->Add(footer);
    yPos += 40;

    card->Height = yPos;
    flow->Controls->Add(card);
  }
}

void courierForm::btnGroupAction_Click(System::Object ^ sender,
                                       System::EventArgs ^ e) {
  Button ^ btn = safe_cast<Button ^>(sender);
  String ^ tag = btn->Tag->ToString();
  array<String ^> ^ parts = tag->Split('|');
  int actionMode = Convert::ToInt32(parts[0]);
  // parts[1] = custID (unused directly)
  array<String ^> ^ transIDs = parts[2]->Split(',');

  if (actionMode == 1) {
    // Claim all transactions
    if (MessageBox::Show(L"Ambil " + transIDs->Length +
                             L" pesanan dari pembeli ini?",
                         L"Konfirmasi", MessageBoxButtons::YesNo,
                         MessageBoxIcon::Question) ==
        System::Windows::Forms::DialogResult::Yes) {
      int success = 0, fail = 0;
      for (int i = 0; i < transIDs->Length; i++) {
        int transID = Convert::ToInt32(transIDs[i]);
        if (DatabaseManager::ClaimDelivery(transID, currentUserID))
          success++;
        else
          fail++;
      }
      String ^ msg = L"Berhasil mengambil " + success + L" pesanan.";
      if (fail > 0)
        msg += L"\n" + fail +
               L" pesanan gagal (mungkin sudah diambil kurir lain).";
      MessageBox::Show(msg, L"Hasil", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadPending();
      LoadActive();
      LoadDashboard();
    }
  } else if (actionMode == 2) {
    // Complete all transactions
    if (MessageBox::Show(L"Selesaikan " + transIDs->Length +
                             L" pengiriman?\nAnda akan menerima ongkos kirim.",
                         L"Konfirmasi", MessageBoxButtons::YesNo,
                         MessageBoxIcon::Question) ==
        System::Windows::Forms::DialogResult::Yes) {
      int success = 0, fail = 0;
      for (int i = 0; i < transIDs->Length; i++) {
        int transID = Convert::ToInt32(transIDs[i]);
        if (DatabaseManager::CompleteDelivery(transID, currentUserID))
          success++;
        else
          fail++;
      }
      String ^ msg = L"Berhasil: " + success + L" pengiriman selesai.";
      if (fail > 0)
        msg += L"\n" + fail + L" pengiriman gagal.";
      msg += L"\n\nOngkos kirim telah ditambahkan ke saldo Anda.";
      MessageBox::Show(msg, L"Hasil", MessageBoxButtons::OK,
                       MessageBoxIcon::Information);
      LoadActive();
      LoadHistory();
      LoadDashboard();
    }
  }
}

System::Void courierForm::btnRefreshDashboard_Click(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  LoadDashboard();
  MessageBox::Show("Dashboard diperbarui!", "Info", MessageBoxButtons::OK,
                   MessageBoxIcon::Information);
}

System::Void courierForm::btnRefreshPending_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  LoadPending();
}

System::Void courierForm::btnClaim_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
  // Legacy handler - no longer used, grouped UI handles claims
}

System::Void courierForm::btnRefreshActive_Click(System::Object ^ sender,
                                                 System::EventArgs ^ e) {
  LoadActive();
}

System::Void courierForm::btnComplete_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  // Legacy handler - no longer used, grouped UI handles completions
}

System::Void courierForm::btnRefreshHistory_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  LoadHistory();
}

System::Void courierForm::btnWithdraw_Click(System::Object ^ sender,
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

System::Void courierForm::btnLogout_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
  this->Close();
}

void courierForm::LoadNotifikasi() {
  DataTable ^ dt = DatabaseManager::GetNotifications(currentUserID);
  dgvNotifikasi->DataSource = dt;

  int unread = DatabaseManager::GetUnreadNotificationCount(currentUserID);
  if (unread > 0) {
    tabNotifikasi->Text = L"Notifikasi (" + unread + L")";
  } else {
    tabNotifikasi->Text = L"Notifikasi";
  }

  // Mark as read when tab is viewed
  if (tabControl->SelectedTab == tabNotifikasi) {
    DatabaseManager::MarkNotificationsRead(currentUserID);
    tabNotifikasi->Text = L"Notifikasi";
  }
}

} // namespace ECommerce
