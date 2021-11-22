using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace asm_cs
{
    class InitializationPort
    {

/*
        // Read port Txt
        public static string pathPortTxt = @"C:\Users\resco\Desktop\PartyHard\b2\projet_trans_asm\ports.txt";
        public static string portTxt = System.IO.File.ReadAllText(pathPortTxt).Replace(" :", "");
        public static string[] lines;
        public static string[] dataPort;

        public static string[] SplitByNewLine()
        {
            string[] lines = portTxt.Split(
                new[] { Environment.NewLine },
                StringSplitOptions.None
            );
            return lines;
        }

        public static string[,] SplitInformationAndStockIn2D()
        {
            string[,] dataPort = new string[13, 3];

            for (int i = 0; i < lines.Length; i++)
            {
                string[] temp = lines[i].Split(' ');

                for (int j = 0; j < 3; j++)
                {
                    dataPort[i, j] = temp[j];
                }
            }

        }

        public static void PrintDataPort()
        {
            for (int i = 0; i < dataPort.GetLength(0); i++)
            {
                for (int j = 0; j < dataPort.GetLength(1); j++)
                {
                    Console.Write(dataPort[i, j] + "\t");
                }
                Console.WriteLine();
            }
        }
*/

        public static string ReadPortsTxt()
        {


            // Read port Txt
            string pathPortTxt = @"C:\Users\resco\Desktop\PartyHard\b2\projet_trans_asm\ports.txt";
            string portTxt = System.IO.File.ReadAllText(pathPortTxt).Replace(" :", "");


            // Split by NewLine 
            string[] lines = portTxt.Split(
                new[] { Environment.NewLine },
                StringSplitOptions.None
            );


            // Split by whitespace & stock in array2D
            string[,] dataPort = new string[13, 3];

            for (int i = 0; i < lines.Length; i++)
            {
                string[] temp = lines[i].Split(' ');

                for (int j = 0; j < 3; j++)
                {
                    dataPort[i, j] = temp[j];
                }
            }


            // Print array2D
            for (int i = 0; i < dataPort.GetLength(0); i++)
            {
                for (int j = 0; j < dataPort.GetLength(1); j++)
                {
                    Console.Write(dataPort[i, j] + "\t");
                }
                Console.WriteLine();
            }

            Console.ReadKey(true);
            return portTxt;
        }
    }
}
