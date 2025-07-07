#include "../trait.h"

// Define Entity trait with health field and status method
#define Trait_Entity(X) \
    field(X, int, health) \
    method(X, const char*, get_status)

define_type_from_trait(Entity, Trait_Entity)

// Player struct implementing Entity trait
struct Player {
    char name[64];
    int level;
    use(Trait_Entity)
};

// Player implementation
impl(Player) {
    def(get_status, {
        static char status[128];
        snprintf(status, sizeof(status), "Player %s (Level %d, Health %d)", 
                 self->name, 
                 self->level, 
                 self->health);
        return (const char*)status;
    });
}

// Register Player as implementing Entity trait
struct_impl_trait_type(Player, Entity)

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
    printf("Health: %d\n", *(entity->health));
    printf("Status: %s\n", entity->get_status());
    
    // Modify health through the Entity trait object
    *(entity->health) = 75;
    printf("\nAfter modifying health via Entity trait:\n");
    printf("Entity health: %d\n", *(entity->health));
    printf("Original Player health: %d\n", player->health);
    printf("Both should be the same: %s\n", 
           (*(entity->health) == player->health) ? "YES" : "NO");
    
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
    printf("Entity health: %d\n", *(entity->health));
    printf("Player level: %d\n", player->level);
    printf("Status: %s\n", entity->get_status());
    
    // Clean up
    Entity_destroy(entity);
    Player_destroy(player);
    
    printf("\n=== Test completed successfully! ===\n");
    return 0;
}
