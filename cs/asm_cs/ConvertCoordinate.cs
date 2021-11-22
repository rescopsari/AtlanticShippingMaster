using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace asm_cs
{
    class ConvertCoordinate
    {
        public double ConvertDmsToDd(string coordinate)
        {
            var multiplier = (coordinate.Contains("S") || coordinate.Contains("W")) ? -1 : 1;

            coordinate = Regex.Replace(coordinate, "[^0-9.]", "");

            var coordinateArray = coordinate.Split('.');

            var degrees = Double.Parse(coordinateArray[0]);
            var minutes = Double.Parse(coordinateArray[1]) / 60;
            var seconds = Double.Parse(coordinateArray[2]) / 3600;

            return (degrees + minutes + seconds) * multiplier;
        }
    }
}
