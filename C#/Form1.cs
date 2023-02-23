namespace C_;

public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
        btn1.Click += btn1Click;
        btnPop.Click += popClick;
    }
    private void btn1Click(object sender, EventArgs e)
    {
        string text = textBox1.Text;
        s.Push(text);
        textBox1.Text = "";

        listbox1.Items.Clear();
        foreach(string item in s)
            listbox1.Items.Add(item);
    }
    private void popClick(object sender, EventArgs e)
    {
        s.Pop();
        listbox1.Items.Clear();
        foreach(string item in s)
            listbox1.Items.Add(item);
    }
}