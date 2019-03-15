/*
 * Winter 2019 - CS362 - Final Project Part B
 * Matthew Solbrack, solbracm@oregonstate.edu
 * Sung Hyun Pak, paks@oregonstate.edu
 * Linge Ge, gel@oregonstate.edu
 *
 * Manual tests for the method isValid() in UrlValidator.
 * This would typically be run manually using CLI or GUI.
 */

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest()
   {
      UrlValidator validator=new UrlValidator();
      assertFalse(validator.isValid("http://www.google.com"));
      assertTrue(validator.isValid("http://www.google.com"));

   }

   //Checking the Scheme
   public void testYourFirstPartition()
   {
      UrlValidator validator1=new UrlValidator();
      assertTrue(validator1.isValid("http://www.google.com"));
      assertFalse(validator1.isValid("HTTP://www.google.com"));
   }

   //Checking the Host
   public void testYourSecondPartition(){
      UrlValidator validator1=new UrlValidator();
      assertTrue(validator1.isValid("http://www.google.com"));
      assertFalse(validator1.isValid("http:///.com"));
   }

   //Checking the Path
   public void testYourThirdPartition(){
      UrlValidator validator1=new UrlValidator();
      assertTrue(validator1.isValid("http://www.google.com/"));
      assertFalse(validator1.isValid("http://www.google.com/ /"));
   }

   //Checking the Query
   public void testYourFourthPartition(){
      UrlValidator validator1=new UrlValidator();
      assertTrue(validator1.isValid("http://validator.w3.org/feed/check.cgi?url=http://google.com"));
      assertFalse(validator1.isValid("http://validator.w3.org/feed/check.cgi?url= google.com"));
   }
}