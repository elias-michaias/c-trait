#include "../trait.h"

// Define Entity trait with health field and status method
#define Trait_Entity(X) \
    method(X, const char*, get_status)

define_type_from_trait(Entity, Trait_Entity)

// Player struct implementing Entity trait
struct Player {
    char name[64];
    int level;
    int health;
    use(Trait_Entity)
};

#define STRUCT_IMPL Player
// Player implementation
impl {
    def(get_status, const char* {
        static char status[128];
        snprintf(status, sizeof(status), "Player %s (Level %d, Health %d)", 
                 self->name, 
                 self->level, 
                 self->health);
        return status;
    });
}
// Register Player as implementing Entity trait
impl_traits(Entity)
#undef STRUCT_IMPL

int main() {
    printf("=== Pointer-based Trait Objects Demo ===\n\n");
    
    // Create a Player
    struct Player* player = Player_new();
    strcpy(player->name, "Alice");
    player->level = 5;
    player->health = 100;  // Set initial health
    
    printf("Initial player state:\n");
    printf("Name: %s, Level: %d, Health: %d\n", 
           player->name, player->level, player->health);
    
    // Create Entity trait object from Player
    Entity* entity = Entity_from_Player(player);
    
    printf("\nAccessing via Entity trait:\n");
    printf("Status: %s\n", entity->get_status());
    
    // Modify health through the Player struct directly
    player->health = 75;
    printf("\nAfter modifying health via Player struct:\n");
    printf("Original Player health: %d\n", player->health);
    printf("Status: %s\n", entity->get_status());
    
    // Get back to original Player struct from Entity trait
    struct Player* recovered_player = Player_from_Entity(entity);
    printf("\nRecovered Player from Entity trait:\n");
    printf("Name: %s, Level: %d, Health: %d\n", 
           recovered_player->name, recovered_player->level, recovered_player->health);
    printf("Same object: %s\n", (recovered_player == player) ? "YES" : "NO");
    
    // Modify via recovered player
    recovered_player->level = 6;
    recovered_player->health = 50;
    
    printf("\nAfter modifying via recovered Player:\n");
    printf("Player level: %d\n", player->level);
    printf("Status: %s\n", entity->get_status());
    
    // Clean up
    Entity_destroy(entity);
    Player_destroy(player);
    
    printf("\n=== Test completed successfully! ===\n");
    return 0;
}
