#pragma once
#include "registrationForm.h"

namespace ProjectAffiliate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ labelNama;
	private: System::Windows::Forms::Label^ labelSandi;
	private: System::Windows::Forms::TextBox^ textBoxNama;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ btnDaftar;
	private: System::Windows::Forms::Button^ btnMasuk;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelNama = (gcnew System::Windows::Forms::Label());
			this->labelSandi = (gcnew System::Windows::Forms::Label());
			this->textBoxNama = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btnDaftar = (gcnew System::Windows::Forms::Button());
			this->btnMasuk = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(101, 69);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Login untuk masuk";
			// 
			// labelNama
			// 
			this->labelNama->AutoSize = true;
			this->labelNama->Location = System::Drawing::Point(101, 125);
			this->labelNama->Name = L"labelNama";
			this->labelNama->Size = System::Drawing::Size(33, 13);
			this->labelNama->TabIndex = 1;
			this->labelNama->Text = L"nama";
			// 
			// labelSandi
			// 
			this->labelSandi->AutoSize = true;
			this->labelSandi->Location = System::Drawing::Point(101, 198);
			this->labelSandi->Name = L"labelSandi";
			this->labelSandi->Size = System::Drawing::Size(59, 13);
			this->labelSandi->TabIndex = 2;
			this->labelSandi->Text = L"Kata Sandi";
			// 
			// textBoxNama
			// 
			this->textBoxNama->Location = System::Drawing::Point(104, 142);
			this->textBoxNama->Name = L"textBoxNama";
			this->textBoxNama->Size = System::Drawing::Size(171, 20);
			this->textBoxNama->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(104, 214);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(171, 20);
			this->textBox2->TabIndex = 4;
			// 
			// btnDaftar
			// 
			this->btnDaftar->Location = System::Drawing::Point(104, 257);
			this->btnDaftar->Name = L"btnDaftar";
			this->btnDaftar->Size = System::Drawing::Size(75, 23);
			this->btnDaftar->TabIndex = 5;
			this->btnDaftar->Text = L"Daftar";
			this->btnDaftar->UseVisualStyleBackColor = true;
			this->btnDaftar->Click += gcnew System::EventHandler(this, &MyForm::btnDaftar_Click);
			// 
			// btnMasuk
			// 
			this->btnMasuk->Location = System::Drawing::Point(200, 257);
			this->btnMasuk->Name = L"btnMasuk";
			this->btnMasuk->Size = System::Drawing::Size(75, 23);
			this->btnMasuk->TabIndex = 6;
			this->btnMasuk->Text = L"Masuk";
			this->btnMasuk->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 364);
			this->Controls->Add(this->btnMasuk);
			this->Controls->Add(this->btnDaftar);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBoxNama);
			this->Controls->Add(this->labelSandi);
			this->Controls->Add(this->labelNama);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Login";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnDaftar_Click(System::Object^ sender, System::EventArgs^ e) {
		// Buat instance dari registrationForm
		ProjectAffiliate::MyForm1^ registrationForm = gcnew ProjectAffiliate::MyForm1();
		// Sembunyikan login form
		/*this->Hide();*/
		// Tampilkan registration form
		registrationForm->ShowDialog();
		// Tampilkan kembali login form setelah registration form ditutup
		this->Show();
	}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
