using ExtendedSerialPort;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        
        DispatcherTimer timerAffichage;
        Robot robot;
        

        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 20);
            timerAffichage.Tick += TimerAffichage_Tick; ;
            timerAffichage.Start();
            
            robot = new Robot();
        }

        private void TimerAffichage_Tick(object sender, EventArgs e)
            
        {
            //throw new NotImplementedException();
            if (robot.receivedText != "")
            {
                TextBoxReception.Text = robot.receivedText;
            }
            while (robot.byteListReceived.Count>0) 
            { 
                TextBoxReception.Text= robot.byteListReceived.Dequeue().ToString();
            }
        }

        int compteurBoutonEnvoyer = 0;

        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            for(int i =0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]); 
            }

        }
    
        private void ButtonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            
            if (compteurBoutonEnvoyer == 0){
                ButtonEnvoyer.Background = Brushes.RoyalBlue;
                compteurBoutonEnvoyer = 1;
            }
            else
            {
                ButtonEnvoyer.Background = Brushes.Beige;
                compteurBoutonEnvoyer = 0;
            }

            TextBoxReception.Text +=  "Recu :" + TextBoxEmission.Text + "\n";
            TextBoxEmission.Text = "";
            
        }

        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {
            robot.receivedText = "";
            TextBoxReception.Text = "";
        }

        private void ButtonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList = new byte[20];
            for ( int i=0; i<20; i++)
            {
                byteList[i] = (byte)(2* i);
            }
            serialPort1.Write(byteList, 0, byteList.Length);
            
        }

        private void emissionTextBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                serialPort1.WriteLine(TextBoxEmission.Text);
                TextBoxEmission.Text = "";
                //serialPort1.WriteLine(Messagerie);
                //Messagerie = Messagerie + "Recu :" + emissionTextBox.Text + "\n";
                //RichTextBox.Text = Messagerie;
                //emissionTextBox.Text = " ";
            }
        }
    }
}
