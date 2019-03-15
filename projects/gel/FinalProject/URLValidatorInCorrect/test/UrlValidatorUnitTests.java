/*
 * Winter 2019 - CS362 - Final Project Part B
 * Matthew Solbrack, solbracm@oregonstate.edu
 * Sung Hyun Pak, paks@oregonstate.edu
 * Linge Ge, gel@oregonstate.edu
 *
 * Unit tests for the method isValid() in UrlValidator.
 * Full statement and branch coverage.
 */

import static org.junit.Assert.*;
import static org.mockito.Mockito.*;
import static org.mockito.Matchers.*;
import java.io.Serializable;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Collections;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class UrlValidatorUnitTests extends TestCase {
   public UrlValidatorUnitTests(String testName) {
      super(testName);
   }

   // mock these classes so that we mock certain methods in them in tests
   Matcher mockUrlMatcher = mock(Matcher.class);
   UrlValidator mockUrlValidator = mock(UrlValidator.class);
   String mockString = mock(String.class);

   public void testNullValuesAreRejected() {
      // Arrange/Mock
      UrlValidator validator = new UrlValidator();
      String value = null;

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testUrlMatcherIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testIsValidSchemeIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testIsValidAuthorityIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockString.equals(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testIsValidPathIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockString.equals(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testIsValidQueryIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockString.equals(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testIsValidFragmentIsFalse() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockString.equals(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidFragment(anyString())).thenReturn(false);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testPassAllValidations() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockString.equals(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidFragment(anyString())).thenReturn(true);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, true);
   }

   public void testValidSpecialCaseFileWithColonAuthority() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_AUTHORITY)).thenReturn("not null");
      when(mockString.equals(anyString())).thenReturn(true);
      when(mockString.contains(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidFragment(anyString())).thenReturn(true);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, false);
   }

   public void testValidSpecialCaseFileWithNullAuthority() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_AUTHORITY)).thenReturn(null);
      when(mockString.equals(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidFragment(anyString())).thenReturn(true);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, true);
   }

   public void testValidSpecialCaseFileWithoutColonAuthority() {
      // Arrange/Mock
      when(mockUrlMatcher.matches()).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_SCHEME)).thenReturn("file");
      when(mockUrlValidator.isValidScheme(anyString())).thenReturn(true);
      when(mockUrlMatcher.group(PARSE_URL_AUTHORITY)).thenReturn("not null");
      when(mockString.equals(anyString())).thenReturn(true);
      when(mockString.contains(anyString())).thenReturn(false);
      when(mockUrlValidator.isValidAuthority(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidPath(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidQuery(anyString())).thenReturn(true);
      when(mockUrlValidator.isValidFragment(anyString())).thenReturn(true);

      UrlValidator validator = new UrlValidator();
      String value = 'asdf';

      // Act
      boolean result = validator.isValid(value)

      // Assert
      assertEquals(result, true);
   }
}