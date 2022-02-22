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

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);

        }
        int compteurBoutonEnvoyer = 0;
        string Messagerie="";
    
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
            Messagerie = Messagerie + "Recu :" + emissionTextBox.Text + "\n";
            RichTextBox.Text = Messagerie;
            emissionTextBox.Text = " ";
            
        }

        private void emissionTextBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                Messagerie = Messagerie + "Recu :" + emissionTextBox.Text + "\n";
                RichTextBox.Text = Messagerie;
                emissionTextBox.Text = " ";
            }
        }
    }
}
