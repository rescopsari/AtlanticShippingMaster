using asm_cs;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace asm_cs_unit_test
{
    [TestClass]
    public class TestCalculTrajet
    {
        [TestMethod]
        public void Test()
        {
            var test = new CalculTrajet();

            Assert.AreEqual(6602, test.formula(51.89, 8.498, 18.62819, 72.31619));
        }
    }
}