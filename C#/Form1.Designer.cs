namespace C_;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        s = new Stack<string>();

        this.components = new System.ComponentModel.Container();
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(450, 450);
        this.Text = "Form1";

        btn1 = new Button();
        btn1.Text = "click me!";
        btn1.Location = new System.Drawing.Point(125,50);
        this.Controls.Add(btn1);
        btnPop = new Button();
        btnPop.Text= "Pop item";
        btnPop.Location = new System.Drawing.Point(249,50);
        this.Controls.Add(btnPop);

        textBox1 = new TextBox();
        textBox1.Location = new System.Drawing.Point(125, 100);
        this.Controls.Add(textBox1);
        
        listbox1 = new ListBox();
        listbox1.Location = new System.Drawing.Point(125,150);
        listbox1.Size = new System.Drawing.Size(200,150);
        this.Controls.Add(listbox1);  

              
    }

//private section
    private Button btn1, btnPop;
    private Stack<string> s;
    private TextBox textBox1;
    private ListBox listbox1;

    #endregion
}
