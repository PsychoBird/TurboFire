uint16_t calculate_rank_strength(int *ranks) {
    int i, r;
    int counts[13] = {0};  // Histogram
    uint16_t bit_mask = 0; // Straight detector

    // --- STEP 1: POPULATE HISTOGRAM & BITMASK ---
    for (i = 0; i < 7; i++) {
        r = ranks[i];
        counts[r]++;
        bit_mask |= (1 << r);
    }

    // --- STEP 2: FIND GROUPS (Quads, Trips, Pairs) ---
    // Scan backwards (Ace down to 2) to prioritize higher ranks
    int four = -1, three = -1, pair1 = -1, pair2 = -1;

    for (i = 12; i >= 0; i--) {
        if (counts[i] == 4) four = i;
        else if (counts[i] == 3) {
            if (three == -1) three = i;
            else if (pair1 == -1) pair1 = i; // Demote old trips to pair
        }
        else if (counts[i] == 2) {
            if (pair1 == -1) pair1 = i;
            else if (pair2 == -1) pair2 = i;
        }
    }

    // --- STEP 3: EVALUATE HIERARCHY ---

    // 1. QUADS
    if (four != -1) {
        int kicker = -1;
        // Find best kicker (skip the quad rank)
        for (i = 12; i >= 0; i--) {
            if (counts[i] > 0 && i != four) {
                kicker = i;
                break;
            }
        }
        // Normalize kicker (0-11)
        if (kicker > four) kicker--;
        
        // Math: Base + (QuadRank * 12) + Kicker + 1
        return QUADS_FLOOR + (four * 12) + kicker + 1;
    }

    // 2. FULL HOUSE
    if (three != -1 && pair1 != -1) {
        // Normalize pair rank (0-11)
        if (pair1 > three) pair1--;
        
        // Math: Base + (TripRank * 12) + PairRank + 1
        return FULL_HOUSE_FLOOR + (three * 12) + pair1 + 1;
    }

    // 3. STRAIGHTS
    // Check Broadways (Ace-High) down to 6-High
    for (i = 8; i >= 0; i--) {
        if (((bit_mask >> i) & 0x1F) == 0x1F) {
            // FIX: +2 so 6-high (i=0) sits ABOVE the Wheel
            return STRAIGHT_FLOOR + (i + 2); 
        }
    }
    // Check Wheel (A-2-3-4-5)
    if ((bit_mask & 0x100F) == 0x100F) {
        // FIX: +1 so Wheel sits ABOVE the Floor
        return STRAIGHT_FLOOR + 1; 
    }

    // 4. TRIPS
    if (three != -1) {
        int k1 = -1, k2 = -1;
        // Find 2 best kickers
        for (i = 12; i >= 0; i--) {
            if (counts[i] > 0 && i != three) {
                if (k1 == -1) k1 = i;
                else { k2 = i; break; }
            }
        }
        // Normalize kickers
        if (k1 > three) k1--;
        if (k2 > three) k2--;
        
        // Math: Base + (TripRank * 66) + Combinations + 1
        return TRIPS_FLOOR + (three * 66) + nCk[k1][2] + nCk[k2][1] + 1;
    }

    // 5. TWO PAIR
    if (pair1 != -1 && pair2 != -1) {
        int kicker = -1;
        // Find 1 kicker
        for (i = 12; i >= 0; i--) {
            if (counts[i] > 0 && i != pair1 && i != pair2) {
                kicker = i;
                break;
            }
        }
        // Normalize kicker
        if (kicker > pair1) kicker--;
        if (kicker > pair2) kicker--; 
        
        // Math: Base + (PairCombo * 11) + Kicker + 1
        int pair_score = nCk[pair1][2] + nCk[pair2][1];
        return TWO_PAIR_FLOOR + (pair_score * 11) + kicker + 1;
    }

    // 6. ONE PAIR
    if (pair1 != -1) {
        int k[3], idx = 0;
        // Find 3 kickers
        for (i = 12; i >= 0; i--) {
            if (counts[i] > 0 && i != pair1) {
                k[idx] = i;
                if (k[idx] > pair1) k[idx]--; // Normalize immediately
                idx++;
                if (idx == 3) break;
            }
        }
        
        // Math: Base + (PairRank * 220) + Combinations + 1
        int k_score = nCk[k[0]][3] + nCk[k[1]][2] + nCk[k[2]][1];
        return ONE_PAIR_FLOOR + (pair1 * 220) + k_score + 1;
    }

    // 7. HIGH CARD
    int k[5], idx = 0;
    // Find top 5 cards
    for (i = 12; i >= 0; i--) {
        if (counts[i] > 0) {
            k[idx++] = i;
            if (idx == 5) break;
        }
    }
    
    // Math: Base + Combinations + 1
    int score = nCk[k[0]][5] + nCk[k[1]][4] + nCk[k[2]][3] + nCk[k[3]][2] + nCk[k[4]][1];
    return HIGH_CARD_FLOOR + score + 1;
}
