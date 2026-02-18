int getMaxClusterSize()
        {
            // Clustering concept is mainly relevant for Open Addressing
            if (colType == CHAINING) return 0; 

            int maxCluster = 0;
            int currentCluster = 0;

            // 1. Standard linear scan
            for (int i = 0; i < tableSize; i++)
            {
                if (openTable[i].state == OCCUPIED)
                {
                    currentCluster++;
                }
                else
                {
                    if (currentCluster > maxCluster) maxCluster = currentCluster;
                    currentCluster = 0;
                }
            }
            // Check if the cluster ended at the last element
            if (currentCluster > maxCluster) maxCluster = currentCluster;

            // 2. Handle Wrap-around (if table starts and ends with OCCUPIED)
            if (tableSize > 0 && openTable[0].state == OCCUPIED && openTable[tableSize - 1].state == OCCUPIED)
            {
                // If the whole table is full, maxCluster is already correct (tableSize)
                if (maxCluster < tableSize) 
                {
                    int startLen = 0;
                    for (int i = 0; i < tableSize && openTable[i].state == OCCUPIED; i++) startLen++;

                    int endLen = 0;
                    for (int i = tableSize - 1; i >= 0 && openTable[i].state == OCCUPIED; i--) endLen++;

                    if (startLen + endLen > maxCluster)
                    {
                        maxCluster = startLen + endLen;
                    }
                }
            }

            return maxCluster;
        }