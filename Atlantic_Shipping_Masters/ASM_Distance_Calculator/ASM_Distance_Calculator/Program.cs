using System;
using System.Collections.Generic;
using System.Device.Location;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace ASM_Distance_Calculator
{
    class Program
    {
        public static int Calcul()
        {
            double ConvertDegreeAngleToDouble(string point)
            {
                var multiplier = (point.Contains("S") || point.Contains("W")) ? -1 : 1;

                point = Regex.Replace(point, "[^0-9.°']", "");
                point = point.Replace('°', ':');
                point = point.Replace('\'', ':');
                point = point.Replace('.', ',');

                var pointArray = point.Split(':');

                var degrees = Double.Parse(pointArray[0]);
                var minutes = Double.Parse(pointArray[1]) / 60;
                var seconds = Double.Parse(pointArray[2]) / 3600;

                return (degrees + minutes + seconds) * multiplier;
            }

            double CalcDistance((double lat, double lng) coordA, (double lat, double lng) coordB)
            {
                var sCoord = new GeoCoordinate(coordA.lat, coordA.lng);
                var eCoord = new GeoCoordinate(coordB.lat, coordB.lng);

                return sCoord.GetDistanceTo(eCoord);
            }

            string path = @"./assets/ports.txt";
            string[] lines = File.ReadAllLines(path);
            var ports = new Dictionary<string, (double lat, double lng)>();

            foreach (string line in lines)
            {
                string[] port = line.Split(';');
                var coord = (ConvertDegreeAngleToDouble(port[1]), ConvertDegreeAngleToDouble(port[2]));
                ports.Add(port[0], coord);
            }

            // var distances = new Dictionary<(string start, string end), double>();

            for (int start = 0; start < ports.Count; start++)
            {
                KeyValuePair<string, (double lat, double lng)> portStart = ports.ElementAt(start);
                for (int end = 0; end < ports.Count; end++)
                {
                    KeyValuePair<string, (double lat, double lng)> portDest = ports.ElementAt(end);
                    //distances.Add((portStart.Key, portDest.Key), CalcDistance(portStart.Value, portDest.Value));
                    // Console.WriteLine($"{compteur} - Port de Départ : {portStart.Key} ---> Port d'Arrivée : {portDest.Key} ||| Distance : {distances[(portStart.Key, portDest.Key)]}m \n");
                    Console.WriteLine($"{portStart.Key}:{portDest.Key}:{CalcDistance(portStart.Value, portDest.Value)}:{portStart.Value.lat}:{portStart.Value.lng}");
                }
            }
            //Console.ReadKey();
            return 0;
        }
        private static void Main() => Calcul();
    }
}