#pragma once

namespace ECommerce {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for customerForm
/// </summary>
public
ref class customerForm : public System::Windows::Forms::Form {
public:
  customerForm(void) {
    InitializeComponent();
    //
    // TODO: Add the constructor code here
    //
  }

protected:
  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  ~customerForm() {
    if (components) {
      delete components;
    }
  }

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
    this->SuspendLayout();
    //
    // customerForm
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(284, 261);
    this->Name = L"customerForm";
    this->Text = L"Customer";
    this->Load +=
        gcnew System::EventHandler(this, &customerForm::customerForm_Load);
    this->ResumeLayout(false);
  }
#pragma endregion

  // ========== Event Handlers (implementations in customerForm.cpp) ==========
private:
  System::Void customerForm_Load(System::Object ^ sender,
                                 System::EventArgs ^ e);
};
} // namespace ECommerce
