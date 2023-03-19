using System;
using System.Collections.Generic;
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

using System.IO.Ports;
using System.Threading;

using System.Diagnostics;
using System.Windows.Navigation;


namespace macropad.final
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        

        System.IO.Ports.SerialPort serpor = new System.IO.Ports.SerialPort();

        public MainWindow()
        {
            InitializeComponent();
        }
        private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            // for .NET Core you need to add UseShellExecute = true
            // see https://learn.microsoft.com/dotnet/api/system.diagnostics.processstartinfo.useshellexecute#property-value
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }

        private void comcheck_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }

        
        private void Aktualisieren_Click(object sender, RoutedEventArgs e)
        {
            string pn = comcheck.SelectedValue.ToString();
            serpor.PortName = pn;
        }

        private void Layout_Click(object sender, RoutedEventArgs e)
        {
            serpor.Open();
            serpor.WriteLine("displ_layout");
            serpor.Close();
        }

        private void Uhrzeit_Click(object sender, RoutedEventArgs e)
        {
            serpor.Open();
            serpor.WriteLine("displ_set time");
            Thread.Sleep(1000);
            serpor.WriteLine(DateTime.Now.ToString("HH"));
            Thread.Sleep(1000);
            serpor.WriteLine(DateTime.Now.ToString("mm"));
            serpor.Close();
        }
        private void Off_Click(object sender, RoutedEventArgs e)
        {
            serpor.Open();
            serpor.WriteLine("displ_off");
            serpor.Close();
        }

        private void Fade_Click(object sender, RoutedEventArgs e)
        {
            serpor.Open();
            serpor.WriteLine("set rgb_fade");
            serpor.Close();
        }

        private void Custom_Click(object sender, RoutedEventArgs e)
        {
            string sliderRval = sliderR.Value.ToString();
            string sliderGval = sliderG.Value.ToString();
            string sliderBval = sliderB.Value.ToString();
            serpor.Open();
            serpor.WriteLine("set rgb_custom color");
            Thread.Sleep(1000);
            serpor.WriteLine(sliderRval);
            Thread.Sleep(1000);
            serpor.WriteLine(sliderGval);
            Thread.Sleep(1000);
            serpor.WriteLine(sliderBval);
            serpor.Close();
        }

        private void sliderR_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            
        }

        private void sliderG_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void sliderB_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            serpor.BaudRate = (115200);
        }

        
    }
}
