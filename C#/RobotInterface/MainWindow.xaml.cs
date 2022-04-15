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
            serialPort1 = new ReliableSerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
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
            //if (robot.receivedText != "")
            //{
            //    TextBoxReception.Text = robot.receivedText;
            //}
            while (robot.byteListReceived.Count>0) 
            {

                //TextBoxReception.Text= robot.byteListReceived.Dequeue().ToString();
                var c = robot.byteListReceived.Dequeue();
                DecodeMessage(c);
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

            //TextBoxReception.Text +=  "Recu :" + TextBoxEmission.Text + "\n";
            TextBoxEmission.Text = "";
            
        }

        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {
            robot.receivedText = "";
            TextBoxReception.Text = "";
        }

        private void ButtonTest_Click(object sender, RoutedEventArgs e)
        {
            //byte[] byteList = new byte[20];
            //for ( int i=0; i<20; i++)
            //{
            //    byteList[i] = (byte)(2* i);
            //}
            //serialPort1.Write(byteList, 0, byteList.Length);
            string s = "Bonjour";
            byte[] array = Encoding.ASCII.GetBytes(s);

            UartEncodeAndSendMessage(0x0080, (ushort)array.Length, array);


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
        byte CalculateChecksum(UInt16 msgFunction, UInt16 msgPayloadLength, byte[] msgPayload)
        {
            byte checksum = 0;
            checksum ^= 0xFE;
            checksum ^= (byte)(msgFunction >> 8);
            checksum ^= (byte)(msgFunction >> 0);
            checksum ^= (byte)(msgPayloadLength >> 8);
            checksum ^= (byte)(msgPayloadLength >> 0);

            for (int i = 0; i <msgPayloadLength; i++)
            {
                checksum ^= msgPayload[i];
            }
            return checksum;
        }
        void UartEncodeAndSendMessage(UInt16 msgFunction, UInt16 msgPayloadLength, byte[] msgPayload)
        {
            byte[] trame = new byte[msgPayloadLength+6];
            int pos = 0;

            trame[pos++] = 0xFE;
            trame[pos++] = (byte)(msgFunction>>8);
            trame[pos++] = (byte)(msgFunction>>0);
            trame[pos++] = (byte)(msgPayloadLength >> 8);
            trame[pos++] = (byte)(msgPayloadLength >> 0);
            for(int i = 0; i < msgPayloadLength; i++)
            {
                trame[pos++] = msgPayload[i];
            }
            trame[pos++] = CalculateChecksum(msgFunction,msgPayloadLength,msgPayload);
            serialPort1.Write(trame, 0, pos);
        }

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }

        StateReception rcvState = StateReception.Waiting;
        UInt16 msgDecodedFunction = 0;
        UInt16 msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;

        private void DecodeMessage(byte c)
        {
            switch(rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                        rcvState = StateReception.FunctionMSB;
                    break;
                case StateReception.FunctionMSB:
                    msgDecodedFunction =(UInt16)(c << 8);
                    rcvState = StateReception.FunctionLSB;
                    break;
                case StateReception.FunctionLSB:
                    msgDecodedFunction += c;
                    rcvState = StateReception.PayloadLengthMSB;
                    break;
                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength = (UInt16)(c << 8);
                    rcvState = StateReception.PayloadLengthLSB;
                    break;
                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength += c;
                    if (msgDecodedPayloadLength == 0)
                        rcvState = StateReception.CheckSum;
                    else
                    {
                        rcvState = StateReception.Payload;
                        msgDecodedPayloadIndex = 0;
                        msgDecodedPayload = new byte[msgDecodedPayloadLength];
                    }
                    break;
                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex] = c;
                    msgDecodedPayloadIndex++;
                    if (msgDecodedPayloadIndex >= msgDecodedPayloadLength)
                        rcvState = StateReception.CheckSum;
                    break;
                case StateReception.CheckSum:
                    var calcChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    if (calcChecksum == c)
                    {
                        TextBoxReception.Text += "\nChecksums cohérent";
                    }
                    else
                    {
                        TextBoxReception.Text += "\nChecksums incohérent";
                    }
                    rcvState = StateReception.Waiting;
                    break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }
    }
}
