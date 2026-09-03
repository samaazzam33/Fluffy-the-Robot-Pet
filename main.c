#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STAT_MAX     10U
#define LOW_WARNING   3U
#define NAME_LEN     12U

#define BIT_ASLEEP    0U
#define BIT_HUNGRY    1U
#define BIT_SAD       2U
#define BIT_SICK      3U

#define SET_BIT(reg, n)  ((reg) |= (uint8_t)(1U << (n)))
#define CLR_BIT(reg, n)  ((reg) &= (uint8_t)~(1U << (n)))
#define READ_BIT(reg, n) ((uint8_t)(((reg) >> (n)) & 1U))

typedef struct {
    char name[NAME_LEN];
    uint8_t food;
    uint8_t fun;
    uint8_t energy;
    uint8_t mood;
    uint16_t hours;
} Pet_t;

static Pet_t fluffy;

static void hatchPet(void);
static void drawFace(void);
static void drawStat(const char *label, uint8_t value);
static void feed(void);
static void play(void);
static void sleepPet(void);
static void hourPasses(void);
static void updateMood(void);
static uint8_t isHappy(void);
static void petReport(void);

static void hatchPet(void)
{
    printf("Enter Fluffy's name: ");

    if (scanf("%11s", fluffy.name) != 1) {
        printf("Invalid name.\n");
        return;
    }

    fluffy.food = STAT_MAX;
    fluffy.fun = STAT_MAX;
    fluffy.energy = STAT_MAX;
    fluffy.hours = 0U;

    CLR_BIT(fluffy.mood, BIT_ASLEEP);
    CLR_BIT(fluffy.mood, BIT_HUNGRY);
    CLR_BIT(fluffy.mood, BIT_SAD);
    CLR_BIT(fluffy.mood, BIT_SICK);

    printf("%s has hatched!\n", fluffy.name);
}

static void drawFace(void)
{
    printf("\n");

    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        printf("  (-_-)\n");
        printf("  Zzz...\n");
    } else if (READ_BIT(fluffy.mood, BIT_SICK)) {
        printf("  (x_x)\n");
    } else if (READ_BIT(fluffy.mood, BIT_SAD)) {
        printf("  (T_T)\n");
    } else if (isHappy()) {
        printf("  (^_^)\n");
    } else {
        printf("  (._.)\n");
    }
}

static void drawStat(const char *label, uint8_t value)
{
    uint8_t i;

    printf("%-7s [", label);

    for (i = 0U; i < STAT_MAX; i++) {
        if (i < value) {
            printf("#");
        } else {
            printf("-");
        }
    }

    printf("] %u/10\n", (unsigned int)value);
}

static void feed(void)
{
    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        printf("Fluffy is sleeping.\n");
        return;
    }

    if (fluffy.food == STAT_MAX) {
        SET_BIT(fluffy.mood, BIT_SICK);
        printf("Fluffy was already full and feels sick.\n");
        return;
    }

    fluffy.food = (fluffy.food + 3U > STAT_MAX)
                    ? STAT_MAX
                    : (uint8_t)(fluffy.food + 3U);

    printf("Fluffy ate some food.\n");
    updateMood();
}

static void play(void)
{
    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        printf("Fluffy is sleeping.\n");
        return;
    }

    fluffy.fun = (fluffy.fun + 3U > STAT_MAX)
                 ? STAT_MAX
                 : (uint8_t)(fluffy.fun + 3U);

    if (fluffy.energy >= 2U) {
        fluffy.energy -= 2U;
    } else {
        fluffy.energy = 0U;
    }

    printf("Fluffy played with you.\n");
    updateMood();
}

static void sleepPet(void)
{
    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        CLR_BIT(fluffy.mood, BIT_ASLEEP);
        printf("Fluffy woke up.\n");
    } else {
        SET_BIT(fluffy.mood, BIT_ASLEEP);
        printf("Fluffy went to sleep.\n");
    }

    updateMood();
}

static void hourPasses(void)
{
    if (fluffy.food > 0U) {
        fluffy.food--;
    }

    if (fluffy.fun > 0U) {
        fluffy.fun--;
    }

    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        fluffy.energy = (fluffy.energy + 2U > STAT_MAX)
                        ? STAT_MAX
                        : (uint8_t)(fluffy.energy + 2U);
    } else if (fluffy.energy > 0U) {
        fluffy.energy--;
    }

    fluffy.hours++;
    updateMood();

    printf("One hour passed.\n");
}

static void updateMood(void)
{
    if (fluffy.food <= LOW_WARNING) {
        SET_BIT(fluffy.mood, BIT_HUNGRY);
    } else {
        CLR_BIT(fluffy.mood, BIT_HUNGRY);
    }

    if (fluffy.fun <= LOW_WARNING) {
        SET_BIT(fluffy.mood, BIT_SAD);
    } else {
        CLR_BIT(fluffy.mood, BIT_SAD);
    }

    if (fluffy.energy == 0U) {
        SET_BIT(fluffy.mood, BIT_ASLEEP);
    }

    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        CLR_BIT(fluffy.mood, BIT_SICK);
    }
}

static uint8_t isHappy(void)
{
    if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        return 0U;
    }

    if (READ_BIT(fluffy.mood, BIT_HUNGRY)) {
        return 0U;
    }

    if (READ_BIT(fluffy.mood, BIT_SAD)) {
        return 0U;
    }

    if (READ_BIT(fluffy.mood, BIT_SICK)) {
        return 0U;
    }

    return (uint8_t)(fluffy.food > LOW_WARNING &&
                     fluffy.fun > LOW_WARNING &&
                     fluffy.energy > LOW_WARNING);
}

static void petReport(void)
{
    printf("\n===== FLUFFY CARE CARD =====\n");
    printf("Name: %s\n", fluffy.name);
    printf("Hours: %u\n", (unsigned int)fluffy.hours);

    drawFace();
    drawStat("Food", fluffy.food);
    drawStat("Fun", fluffy.fun);
    drawStat("Energy", fluffy.energy);

    printf("Mood: %02X\n", (unsigned int)fluffy.mood);

    if (READ_BIT(fluffy.mood, BIT_SICK)) {
        printf("Next need: Sleep to recover.\n");
    } else if (READ_BIT(fluffy.mood, BIT_HUNGRY)) {
        printf("Next need: Food.\n");
    } else if (READ_BIT(fluffy.mood, BIT_SAD)) {
        printf("Next need: Play.\n");
    } else if (READ_BIT(fluffy.mood, BIT_ASLEEP)) {
        printf("Next need: Keep sleeping.\n");
    } else {
        printf("Next need: Nothing. Fluffy is happy!\n");
    }
}

int main(void)
{
    unsigned int choice;

    hatchPet();

    do {
        printf("\n===== FLUFFY ROBOT PET =====\n");
        printf("1. Draw Face\n");
        printf("2. Feed\n");
        printf("3. Play\n");
        printf("4. Sleep/Wake\n");
        printf("5. Pass One Hour\n");
        printf("6. Pet Report\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%u", &choice) != 1) {
            printf("Invalid input.\n");
            scanf("%*s");
            continue;
        }

        switch (choice) {
        case 1: drawFace(); break;
        case 2: feed(); break;
        case 3: play(); break;
        case 4: sleepPet(); break;
        case 5: hourPasses(); break;
        case 6: petReport(); break;
        case 0: printf("Goodbye.\n"); break;
        default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 0U);

    return 0;
}