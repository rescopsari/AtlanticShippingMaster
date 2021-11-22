using System;

namespace asm_cs
{
    public class CalculTrajet
    {
        public int formula(double lat1, double long1, double lat2, double long2)
        {
            int R = 6371; //diamètre de la Terre
            var phi1 = lat1 * Math.PI / 180;
            var phi2 = lat2 * Math.PI / 180;
            var deltaPhi = (lat2 - lat1) * Math.PI / 180;
            var deltaLambda = (long2 - long1) * Math.PI / 180;

            var a = Math.Sin(deltaPhi / 2) * Math.Sin(deltaPhi / 2) +
                    Math.Cos(phi1) * Math.Cos(phi2) *
                    Math.Sin(deltaLambda / 2) * Math.Sin(deltaLambda / 2);

            var c = 2 * Math.Atan2(Math.Sqrt(a), Math.Sqrt(1 - a));
            
            int d = (int) Math.Ceiling(R * c) -1; // Pourquoi -1?

            return d;
        }
    }
}
