declare module "minecraft" {
  export class UUID {
    constructor(uuid: string);

    asString(): string;

    static canParse(uuid: string): boolean;

    static fromString(uuid: string): UUID;
  }

  export class Player {
    get uuid(): UUID;
    get realName(): string;

    sendMessage(message: string): void;

    /**
     * Determine if a player is an administrator of the server
     * @return Returns true if the player
     * is an administrator of the server; otherwise returns false
     * @warning Custom permissions are not considered
     * administrators
     */
    isOperator(): boolean;

    /**
     * Get the name of the player's langtext.
     * @return The name of the player's langtext.
     *
     * @warning This is not the player's in-game nickname.
     */
    getLocaleCode(): string;
  }
}
