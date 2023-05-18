#include <cs50.h>
#include <stdio.h>

int main(void)
{
   long cardnumber = get_long ("card number: ");
   int digitcounter = 1;
   int luhm;
   int digit13;
   int digit14;
   int digit15;
   int digit16;
   for(int i = 0; i < cardnumber; i *= 10)
   {
      long digit = cardnumber % 10;
      cardnumber = cardnumber / 10;
      if (digitcounter == 13)
      {
         digit13 = digit;
      }
      if (digitcounter == 14)
      {
         digit14 = digit;
      }
      if (digitcounter == 15)
      {
         digit15 = digit;
      }
      if (digitcounter == 16)
      {
         digit16 = digit;
      }
      if (digitcounter % 2 == 0)
      {
         digit = digit * 2;
         luhm = luhm + (digit % 10);
         if ((digit % 100) >= 10)
         {
            luhm = luhm + ((digit % 100)/ 10);
         }
      }
      else
      {
         luhm = luhm + digit;
      }
      digitcounter++;
   }
   if (luhm % 10 > 0)
   {
      printf("INVALID\n");
   }
   if (luhm % 10 == 0)
   {
      if (digitcounter - 1 == 15)
      {
         if ((digit14 == (4 | 7)) && (digit15 == 3))
         {
            printf("AMEX\n");
         }
         else
         {
            printf("INVALID\n");
         }
      }
      else if (digitcounter - 1 == 16)
      {
         if ((digit15 > 0 && digit15 < 6) && (digit16 == 5))
         {
            printf("MASTERCARD\n");
         }
         else if (digit16 == 4)
         {
            printf("VISA\n");
         }
         else
         {
            printf("INVALID\n");
         }
      }
      else if (digitcounter - 1 == 13)
      {
         if (digit13 == 4)
         {
            printf("VISA\n");
         }
         else
         {
            printf("INVALID\n");
         }
      }
      else
      {
         printf("INVALID\n");
      }
   }
}
