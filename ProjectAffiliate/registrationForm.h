#pragma once

namespace ECommerce
{

	/// <summary>
	/// Summary for registerF
	/// </summary>
	public ref class registerF : public System::Windows::Forms::Form
	{
	public:
		registerF(void)
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
		~registerF()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnKembali;
	protected:
	private: System::Windows::Forms::Button^ btnDaftar;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBoxNama;
	private: System::Windows::Forms::Label^ labelSandi;
	private: System::Windows::Forms::Label^ labelNama;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnKembali = (gcnew System::Windows::Forms::Button());
			this->btnDaftar = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxNama = (gcnew System::Windows::Forms::TextBox());
			this->labelSandi = (gcnew System::Windows::Forms::Label());
			this->labelNama = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// btnKembali
			// 
			this->btnKembali->Location = System::Drawing::Point(104, 274);
			this->btnKembali->Name = L"btnKembali";
			this->btnKembali->Size = System::Drawing::Size(75, 23);
			this->btnKembali->TabIndex = 13;
			this->btnKembali->Text = L"Kembali";
			this->btnKembali->UseVisualStyleBackColor = true;
			this->btnKembali->Click += gcnew System::EventHandler(this, &registerF::btnKembali_Click);
			// 
			// btnDaftar
			// 
			this->btnDaftar->Location = System::Drawing::Point(200, 274);
			this->btnDaftar->Name = L"btnDaftar";
			this->btnDaftar->Size = System::Drawing::Size(75, 23);
			this->btnDaftar->TabIndex = 12;
			this->btnDaftar->Text = L"Daftar";
			this->btnDaftar->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(104, 186);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(171, 20);
			this->textBox2->TabIndex = 11;
			// 
			// textBoxNama
			// 
			this->textBoxNama->Location = System::Drawing::Point(104, 131);
			this->textBoxNama->Name = L"textBoxNama";
			this->textBoxNama->Size = System::Drawing::Size(171, 20);
			this->textBoxNama->TabIndex = 10;
			// 
			// labelSandi
			// 
			this->labelSandi->AutoSize = true;
			this->labelSandi->Location = System::Drawing::Point(101, 170);
			this->labelSandi->Name = L"labelSandi";
			this->labelSandi->Size = System::Drawing::Size(59, 13);
			this->labelSandi->TabIndex = 9;
			this->labelSandi->Text = L"Kata Sandi";
			this->labelSandi->Click += gcnew System::EventHandler(this, &registerF::labelSandi_Click);
			// 
			// labelNama
			// 
			this->labelNama->AutoSize = true;
			this->labelNama->Location = System::Drawing::Point(101, 114);
			this->labelNama->Name = L"labelNama";
			this->labelNama->Size = System::Drawing::Size(33, 13);
			this->labelNama->TabIndex = 8;
			this->labelNama->Text = L"nama";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(101, 81);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Isi untuk daftar";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(104, 213);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(51, 17);
			this->checkBox1->TabIndex = 14;
			this->checkBox1->Text = L"Toko";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(159, 213);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(59, 17);
			this->checkBox2->TabIndex = 15;
			this->checkBox2->Text = L"afiliator";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(224, 213);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(76, 17);
			this->checkBox3->TabIndex = 16;
			this->checkBox3->Text = L"pelanggan";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// registerF
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(376, 372);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->btnKembali);
			this->Controls->Add(this->btnDaftar);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBoxNama);
			this->Controls->Add(this->labelSandi);
			this->Controls->Add(this->labelNama);
			this->Controls->Add(this->label1);
			this->Name = L"registerF";
			this->Text = L"Register";
			this->Load += gcnew System::EventHandler(this, &registerF::registerF_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void registerF_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnKembali_Click(System::Object^ sender, System::EventArgs^ e) {
		// Tutup registration form dan kembali ke login form
		this->Close();
	}
	private: System::Void labelSandi_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
