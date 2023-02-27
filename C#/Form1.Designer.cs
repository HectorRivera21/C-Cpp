namespace C_;

partial class Form1
{
    private System.ComponentModel.IContainer components = null;

    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }
    #region Windows Form Designer generated code
    private void InitializeComponent()
    {
        s = new Stack<double>();

        this.components = new System.ComponentModel.Container();
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(1000, 1000);
        this.Text = "Form1";

        btn1 = new Button();
        btn1.Text = "Calculate";
        btn1.Location = new System.Drawing.Point(400,50);
        btn1.Size = new System.Drawing.Size(150,50);
        this.Controls.Add(btn1);
       
        textBox1 = new TextBox();
        textBox1.Location = new System.Drawing.Point(125, 50);
        textBox1.Size = new System.Drawing.Size(250,50);
        this.Controls.Add(textBox1);
        
        answerHolder = new TextBox();
        answerHolder.Location = new System.Drawing.Point(600,50);
        answerHolder.Size = new System.Drawing.Size(150,100);
        answerHolder.Font = new Font(textBox1.Font, FontStyle.Bold);
        answerHolder.Enabled = false;
        answerHolder.BackColor = Color.LightGray;
        this.Controls.Add(answerHolder);
        
        listbox1 = new ListBox();
        listbox1.Location = new System.Drawing.Point(125,150);
        listbox1.Size = new System.Drawing.Size(300,700);
        this.Controls.Add(listbox1);  

        stackPanel = new Panel();
        stackPanel.Size = new System.Drawing.Size(150, 100);
        stackPanel.Location = new System.Drawing.Point(500, 150);
        stackPanel.Font = new Font(stackPanel.Font, FontStyle.Bold);
        stackPanel.BackColor = Color.LightGray;

        this.Controls.Add(stackPanel);

              
    }

//private section
    private Button btn1;
    private Stack<double> s;
    private TextBox textBox1, answerHolder;
    private ListBox listbox1;
    private Panel stackPanel;

    #endregion
}
