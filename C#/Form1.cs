namespace C_;

public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
        btn1.Click += btn1Click;
    }
    private void btn1Click(object sender, EventArgs e)
    {
        string postfixText = textBox1.Text;
        if(string.IsNullOrEmpty(postfixText)){
            MessageBox.Show("Please enter a postfix expression.");
            return;
        }
        string[] tokens = postfixText.Split(' ');
        foreach (string token in tokens){
            if(double.TryParse(token, out double number)){
                stack_push(number);
            }
            else {
                if(!AppOp(token))
                {
                    MessageBox.Show($"Invalid operator: {token}");
                    return;
                }
            }
        }
        if(s.Count != 0)
        {
            double result = s.Peek();
            answerHolder.Text = result.ToString();
            listbox1.Items.Add("Popped: Answer!");
        }
        else
        {
            MessageBox.Show("Invalid expression.");
        }
    }
    private void UpdateStackDisplay()
    {
        
        stackPanel.Controls.Clear();
        
        for (int i = s.Count - 1; i >= 0; i--)
        {
            Label label = new Label();
            label.Text = s.ElementAt(i).ToString();
            label.AutoSize = false;
            label.TextAlign = ContentAlignment.MiddleCenter;
            label.Dock = DockStyle.Top;
            label.Height = 25;
            
            stackPanel.Controls.Add(label);
        }
    }
    private double stack_pop()
    {
        double popped = s.Pop();
        UpdateStackDisplay();
        MessageBox.Show($"Popping: {popped}");
        listbox1.Items.Add($"Popped: {popped}");
        return popped;
    }

    static bool IsOperator(string token){
        return token == "+"||token == "-"||token == "*"||token == "/";
    }
    private void stack_push(double num){
        s.Push(num);
        MessageBox.Show($"Pushing: {num}");
        listbox1.Items.Add($"Pushed: {num}");
        UpdateStackDisplay();
    }
    private bool AppOp(string op){
        switch(op){
            case"+":
                return TryAdd();
            case"-":
                return TrySubtract();
            case"*":
                return TryMultiply();
            case"/":
                return TryDivide();
            default:
                return false;
        }
    }
    private bool TryAdd()
    {
        if (s.Count < 2) return false;
        MessageBox.Show($"operator found + ");
        listbox1.Items.Add("Performing Operation +");
        double b = stack_pop();
        double a = stack_pop();
        double result = a + b;
        stack_push(result);
        return true;
    }

    private bool TrySubtract()
    {
        if (s.Count < 2) return false;
        MessageBox.Show($"operator found - ");
        listbox1.Items.Add("Performing Operation -");
        double b = stack_pop();
        double a = stack_pop();
        double result = a - b;
        stack_push(result);
        return true;
    }

    private bool TryMultiply()
    {
        if (s.Count < 2) return false;
        MessageBox.Show($"operator found * ");
        listbox1.Items.Add("Performing Operation *");
        double b = stack_pop();
        double a = stack_pop();
        double result = a * b;
        stack_push(result);
        return true;
    }

    private bool TryDivide()
    {
        if (s.Count < 2) return false;
        MessageBox.Show($"operator found / ");
        listbox1.Items.Add("Performing Operation /");
        double b = stack_pop();
        double a = stack_pop();
        if (b == 0)
        {
            s.Push(a);
            s.Push(b);
            return false;
        }
        double result = a / b;
        stack_push(result);
        return true;
    }
}